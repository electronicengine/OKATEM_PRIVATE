#include "spiops.h"
#include "stdlib.h"

#define SECTOR6_ADDRESS 0x08080000


void writeFlash(uint8_t Data, long Address)
{

     HAL_FLASH_Unlock();
     HAL_FLASH_Program(TYPEPROGRAM_BYTE, Address , Data);
     HAL_FLASH_Lock();
}

void readFlash()
{

}




void SPI1_IRQHandler(void)
{

  HAL_SPI_IRQHandler(&hspi1);

  xSemaphoreGiveFromISR(spiSemaphoreHandle, NULL);

}



/* spiComOps function */
void spiComOps(void const * argument)
{

    HAL_SPI_StateTypeDef status;
    unsigned char *var;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
    FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);

    mprintf("spiOps\r\n");

    HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);

    while(1)
    {
        if( xSemaphoreTake(spiSemaphoreHandle, 1) == pdPASS)
        {

            status = HAL_SPI_GetState(&hspi1);
            if(status == HAL_SPI_STATE_READY)
            {

                if(SpiRxData -> header == ('U' | 'P' << 8 ))
                {


                    UpdateFile->total_sequence_number = (SpiRxData->data[0]);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[1] << 8);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[2] << 16);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[3] << 24);

                    UpdateFile->current_sequence_number = (SpiRxData->data[4]);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[5] << 8);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[6] << 16);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[7] << 24);

                    for(int i=0;i<SPI_ENTITY_SIZE; i++)
                    {
                        UpdateFile->data[i] = SpiRxData->data[i+2];
                        writeFlash(UpdateFile -> data[i], SECTOR6_ADDRESS + ((i+1)*UpdateFile->current_sequence_number));
                    }



//                    UpdateFile = (UPDATE_FILE_FORMAT *)(SpiRxData + offsetof(SPI_TRANSFER_FORMAT, header));



                }


                if(SpiRxData -> header == ('C' | 'O' << 8 ))
                {

                    ControlData = (CONTROL_DATA_FORMAT *)SpiRxData + offsetof(SPI_TRANSFER_FORMAT, header);
                    mprintf("%d\r\n", ControlData->x_position);

                }




            }




            xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

            SpiTxData->header = (('E') | (('N') << 8 ));
            memcpy(&SpiTxData->data[0], (unsigned char *)EnvironmentData, SPI_DATA_SIZE);
            memcpy(&SpiTxData->data[99], (unsigned char *)&EnvironmentData->sensor_data, sizeof(SENSOR_DATA));
            SpiTxData->checksum = (('C') | (('H') << 8 ));

            xSemaphoreGive(spiMutexHandle);



            HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);


            if(ControlData -> step_motor1_direction == FORWARD)
            {
                motor1.direction = FORWARD;
                motor1.speed = ControlData -> step_motor1_speed;
            }
            else if(ControlData -> step_motor1_direction == BACKWARD)
            {
                motor1.direction = BACKWARD;
                motor1.speed = ControlData -> step_motor1_speed;
            }
            else
            {
                motor1.direction = STOP;
            }

            if(ControlData -> step_motor2_direction == FORWARD)
            {
                motor2.direction = FORWARD;
                motor1.speed = ControlData -> step_motor2_speed;
            }
            else if(ControlData -> step_motor2_direction == BACKWARD)
            {
                motor2.direction = BACKWARD;
                motor1.speed = ControlData -> step_motor2_speed;
            }
            else
            {
                motor2.direction = STOP;
            }
        }
    }

}

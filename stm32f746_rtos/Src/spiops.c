#include "spiops.h"
#include "stdlib.h"

#define SECTOR6_ADDRESS 0x8080000


void writeFlash(uint8_t Data, long Address)
{


     HAL_FLASH_Program(TYPEPROGRAM_BYTE, Address , (uint8_t) Data);

}



uint8_t readFlash(int Address)
{

    uint8_t flash_data;

    flash_data = *(uint8_t *)Address;

    return flash_data;

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

    unsigned char * update_file;

    mprintf("spiOps\r\n");


    HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);

    while(1)
    {
        if( xSemaphoreTake(spiSemaphoreHandle, 1) == pdPASS)
        {

            status = HAL_SPI_GetState(&hspi1);
            if(status == HAL_SPI_STATE_READY)
            {



                if((SpiRxData->header & 0xff) == 'U' && ((SpiRxData->header >> 8) & 0xff) == 'P')
                {


                    UpdateFile->total_sequence_number = (SpiRxData->data[0]);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[1] << 8);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[2] << 16);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[3] << 24);

                    UpdateFile->current_sequence_number = (SpiRxData->data[4]);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[5] << 8);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[6] << 16);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[7] << 24);

                    mprintf("%d\r\n", UpdateFile->current_sequence_number);

                    if(UpdateFile->current_sequence_number == 1)
                    {
                        update_file = malloc(UpdateFile->total_sequence_number*SPI_ENTITY_SIZE);
                    }

                    for(int i=0;i<SPI_ENTITY_SIZE; i++)
                    {
//                        writeFlash(SpiRxData->data[i + 8], (SECTOR6_ADDRESS + (SPI_ENTITY_SIZE * (UpdateFile->current_sequence_number - 1)) + i));
                        update_file[i + (SPI_ENTITY_SIZE * (UpdateFile->current_sequence_number - 1))] = SpiRxData->data[i + 8];
                    }


                    if(UpdateFile->current_sequence_number == UpdateFile->total_sequence_number)
                    {

                        mprintf("Writing data to memory\r\n");
                        HAL_FLASH_Unlock();
                        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
                        FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);

                        for(int i=0; i<SPI_ENTITY_SIZE*UpdateFile->total_sequence_number; i++)
                        {
                            HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS + i , (uint8_t)update_file[i]);
                            HAL_Delay(20);
                        }

                        HAL_FLASH_Lock();

                        free(update_file);
                        mprintf("Writing is done\r\n");


                    }


//                    if(UpdateFile->total_sequence_number == UpdateFile->current_sequence_number)
//                        HAL_NVIC_SystemReset();


                }

                if((SpiRxData->header & 0xff) == 'C' && ((SpiRxData->header >> 8) & 0xff) == 'O')
                {
                    ControlData = (CONTROL_DATA_FORMAT *)SpiRxData + offsetof(SPI_TRANSFER_FORMAT, header);
                }

                SpiRxData->header = 0;

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

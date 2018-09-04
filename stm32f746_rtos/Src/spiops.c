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

    HAL_StatusTypeDef flash_status;
    HAL_SPI_StateTypeDef status;
    int checksum;
    uint32_t total_size;

    unsigned char * update_file;

    int package_count = 0;
    uint32_t next_package_sequence = 1;
    int missing_package_error = 0;

    short int checksum_error = 0;
    short int sequence_error = 0;

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

                    package_count++;

                    UpdateFile->total_sequence_number = (SpiRxData->data[0]);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[1] << 8);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[2] << 16);
                    UpdateFile->total_sequence_number |= (SpiRxData->data[3] << 24);

                    UpdateFile->current_sequence_number = (SpiRxData->data[4]);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[5] << 8);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[6] << 16);
                    UpdateFile->current_sequence_number |= (SpiRxData->data[7] << 24);

                    checksum = 0;


                    for(int i=0; i<SPI_ENTITY_SIZE; i++)
                       checksum += SpiRxData->data[8 + i];

                    if(checksum != SpiRxData->checksum)
                       checksum_error = 1;

                    if(UpdateFile->current_sequence_number == 1)
                    {
                        update_file = malloc(UpdateFile->total_sequence_number*SPI_ENTITY_SIZE);
                    }

                    for(int i=0;i<SPI_ENTITY_SIZE; i++)
                    {
                        update_file[i + (SPI_ENTITY_SIZE * (UpdateFile->current_sequence_number - 1))] = SpiRxData->data[i + 8];
                    }

                    if(next_package_sequence != 1 && UpdateFile->current_sequence_number != next_package_sequence)
                    {
                        sequence_error = 1;
                    }
                    else
                    {
                        if(checksum_error == 0)
                        {
                            next_package_sequence = UpdateFile->current_sequence_number + 1;
                        }

                    }


                    if(UpdateFile->current_sequence_number == UpdateFile->total_sequence_number)
                    {

                        if(package_count != UpdateFile->total_sequence_number)
                            missing_package_error = 1;


                        mprintf("Writing data to memory\r\n");
                        HAL_FLASH_Unlock();
                        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
                        FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);


                        total_size = SPI_ENTITY_SIZE * UpdateFile->total_sequence_number;


                        flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS, total_size & 0xff);

                        if(flash_status != HAL_OK)
                            mprintf("write error\r\n");

                        flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS + 1, (total_size >> 8) & 0xff);

                        if(flash_status != HAL_OK)
                            mprintf("write error\r\n");

                        flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS + 2, (total_size >> 16) & 0xff);

                        if(flash_status != HAL_OK)
                            mprintf("write error\r\n");

                        flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS + 3, (total_size >> 24) & 0xff);

                        if(flash_status != HAL_OK)
                            mprintf("write error\r\n");

                        for(int i=0; i<total_size; i++)
                        {
                            flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS + i + 4, (uint8_t)update_file[i]);

                            if(flash_status != HAL_OK)
                                mprintf("write error\r\n");
                        }

                        HAL_FLASH_Lock();

                        mprintf("Writing is done\r\n");

                        mprintf("Restarting...\r\n");

                        osDelay(50);

                        free(update_file);

                        HAL_NVIC_SystemReset();



                    }



//                    SpiRxData->header = 0;


                }else if((SpiRxData->header & 0xff) == 'C' && ((SpiRxData->header >> 8) & 0xff) == 'O')
                {
                    ControlData = (CONTROL_DATA_FORMAT *)SpiRxData + offsetof(SPI_TRANSFER_FORMAT, header);

//                    SpiRxData->header = 0;

                }


//                SpiRxData->header = 0;

            }


            xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

            if((SpiRxData->header & 0xff) == 'U' && ((SpiRxData->header >> 8) & 0xff) == 'P')
            {

                    SpiTxData->header = 'U' | 'P' << 8;
                    SpiTxData->data[0] = next_package_sequence & 0xff;
                    SpiTxData->data[1] = (next_package_sequence >>  8) & 0xff;
                    SpiTxData->data[2] = (next_package_sequence >> 16) & 0xff;
                    SpiTxData->data[3] = (next_package_sequence >> 24) & 0xff;

            }
            else
            {

                SpiTxData->header = (('E') | (('N') << 8 ));
                memcpy(&SpiTxData->data[0], (unsigned char *)EnvironmentData, SPI_DATA_SIZE);
                memcpy(&SpiTxData->data[99], (unsigned char *)&EnvironmentData->sensor_data, sizeof(SENSOR_DATA));
                SpiTxData->checksum = (('C') | (('H') << 8 ));

            }

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

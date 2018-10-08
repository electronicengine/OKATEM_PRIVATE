#include "spiops.h"
#include "stdlib.h"

#define SECTOR6_ADDRESS 0x8080000

uint32_t NextUpdateDataPackage = 1;
uint32_t CurrentUpdateDataPackage = 1;


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

    short int ret;
    short int update_data_available = 0;
    short int control_data_available = 0;

    mprintf("spiOps\r\n");

    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
    FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_7, VOLTAGE_RANGE_3);
    HAL_FLASH_Lock();


    HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);

    while(1)
    {

        if( xSemaphoreTake(spiSemaphoreHandle, 1) == pdPASS)  // when interrupt is occured
        {

            status = HAL_SPI_GetState(&hspi1);

            if(status == HAL_SPI_STATE_READY)
            {

                ret = checkIfUpdateData();

                if(ret == HAL_OK)
                {

                    ret = confirmUpdateDataAccuracy();
                    if(ret == HAL_OK)
                        update_data_available = 1;

                    putUpdateDataResponse();


                    motor1.direction = STOP;
                    motor2.direction = STOP;
                    servo1.angle = 0;
                    servo2.angle = 0;
                }
                else
                {
                    ret = checkIfControlData();



                    if(ret == HAL_OK)
                    {

                        control_data_available = 1;

                        putControlDataResponse();

                    }
                    else
                    {
                        putEnvironmentData();

                        motor1.direction = STOP;
                        motor2.direction = STOP;
                        servo1.angle = 0;
                        servo2.angle = 0;
                    }


                }

            }

            HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);

        }




        if(update_data_available == 1)
        {
            processUpdateData();

            update_data_available = 0;
        }
        else if(control_data_available == 1)
        {

            processControlData();

            control_data_available = 0;
        }




    }

}



HAL_StatusTypeDef checkIfUpdateData()
{

    if((SpiRxData->header & 0xff) == 'U' && ((SpiRxData->header >> 8) & 0xff) == 'P')
    {

        memcpy(UpdateFile, SpiRxData->data, SPI_DATA_SIZE);

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }

}



HAL_StatusTypeDef checkIfControlData()
{

    if((SpiRxData->header & 0xff) == 'C' && ((SpiRxData->header >> 8) & 0xff) == 'O')
    {

//        mprintf("%d\r\n", SpiRxData->data[58]);

        ControlData = (CONTROL_DATA_FORMAT *) SpiRxData + offsetof(SPI_TRANSFER_FORMAT, header);

//        memcpy(ControlData, SpiRxData->data, SPI_DATA_SIZE);


        return HAL_OK;

    }
    else
    {

        return HAL_ERROR;

    }
}

HAL_StatusTypeDef confirmUpdateDataAccuracy()
{


    uint16_t checksum = 0;
    short int checksum_error = 0;
    short int sequence_error = 0;

    for(int i=0; i< SPI_ENTITY_SIZE; i++)
        checksum += UpdateFile->data[i];

    if(checksum != SpiRxData->checksum)
        checksum_error = 1;

    if(NextUpdateDataPackage != 1 && UpdateFile->current_sequence_number != NextUpdateDataPackage)
    {
        sequence_error = 1;
    }
    else
    {
        if(checksum_error == 0)
           NextUpdateDataPackage = UpdateFile->current_sequence_number + 1;

    }

     if(sequence_error != 1 && checksum_error != 1)
         return HAL_OK;
     else
         return HAL_ERROR;



}



void putUpdateDataResponse()
{



    xSemaphoreTake(spiMutexHandle, (TickType_t)1000);

    SpiTxData->header = 'U' | 'P' << 8;
    SpiTxData->data[4] = NextUpdateDataPackage & 0xff;
    SpiTxData->data[5] = (NextUpdateDataPackage >>  8) & 0xff;
    SpiTxData->data[6] = (NextUpdateDataPackage >> 16) & 0xff;
    SpiTxData->data[7] = (NextUpdateDataPackage >> 24) & 0xff;

    xSemaphoreGive(spiMutexHandle);

}



void putControlDataResponse()
{

    xSemaphoreTake(spiMutexHandle, (TickType_t)1000);

    SpiTxData->header = (('E') | (('N') << 8 ));
    memcpy(&SpiTxData->data[0], (unsigned char *)EnvironmentData, SPI_DATA_SIZE);
    memcpy(&SpiTxData->data[99], (unsigned char *)&EnvironmentData->sensor_data, sizeof(SENSOR_DATA));
    SpiTxData->checksum = (('C') | (('H') << 8 ));

    xSemaphoreGive(spiMutexHandle);

}



void putEnvironmentData()
{

    xSemaphoreTake(spiMutexHandle, (TickType_t)1000);

    SpiTxData->header = (('E') | (('N') << 8 ));
    memcpy(&SpiTxData->data[0], (unsigned char *)EnvironmentData, SPI_DATA_SIZE);
    memcpy(&SpiTxData->data[99], (unsigned char *)&EnvironmentData->sensor_data, sizeof(SENSOR_DATA));
    SpiTxData->checksum = (('C') | (('H') << 8 ));

    xSemaphoreGive(spiMutexHandle);

}

void processUpdateData()
{


    HAL_StatusTypeDef flash_status;

    if(UpdateFile->current_sequence_number == 1)
    {

        uint32_t total_size = SPI_ENTITY_SIZE*UpdateFile->total_sequence_number;



        HAL_FLASH_Unlock();

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

        HAL_FLASH_Lock();

    }



    HAL_FLASH_Unlock();

    for(int i=0; i<SPI_ENTITY_SIZE; i++)
    {
        flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, (SECTOR6_ADDRESS + i + 4) + (SPI_ENTITY_SIZE * (UpdateFile->current_sequence_number - 1)), (uint8_t)UpdateFile->data[i]);

        if(flash_status != HAL_OK)
            mprintf("write error\r\n");
    }

    HAL_FLASH_Lock();

    if(UpdateFile->current_sequence_number == UpdateFile->total_sequence_number)
    {


        mprintf("Update file uploading has been finished.\r\n");

        mprintf("Restarting...\r\n");

        SpiRxData->header = 0;
        SpiRxData->checksum = 0;
        UpdateFile->current_sequence_number = 0;
        UpdateFile->total_sequence_number = -1;


        osDelay(50);

        HAL_NVIC_SystemReset();


    }


}


void writeUpdateFileToFlash(unsigned char *UpdateFileData)
{


    HAL_StatusTypeDef flash_status;
    uint32_t total_size;


    mprintf("Writing data to memory\r\n");
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
    FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);


    total_size = SPI_ENTITY_SIZE * (UpdateFile->total_sequence_number);


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
        flash_status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, SECTOR6_ADDRESS + i + 4, (uint8_t)UpdateFileData[i]);

        if(flash_status != HAL_OK)
            mprintf("write error\r\n");
    }

    HAL_FLASH_Lock();

    mprintf("Writing is done\r\n");

    mprintf("Restarting...\r\n");

    osDelay(50);


    HAL_NVIC_SystemReset();

}



void processControlData()
{


    motor1.direction = ControlData -> step_motor1_direction;
    motor1.speed = ControlData -> step_motor1_speed;


    motor2.direction = ControlData -> step_motor2_direction;;
    motor2.speed = ControlData -> step_motor2_speed;


//    if(ControlData -> servo_motor1_degree != 0)
    servo1.angle = ControlData -> servo_motor1_degree;


//    if(ControlData -> servo_motor2_degree != 0)
    servo2.angle = ControlData -> servo_motor2_degree;


    if(ControlData -> calibrate_sensor == 1)
    {
        mprintf("S\r\n");

        calibration.available = 1;

        motor1.direction = STOP;
        motor2.direction = STOP;

    }




}




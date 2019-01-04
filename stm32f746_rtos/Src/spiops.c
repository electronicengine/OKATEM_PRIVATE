#include "spiops.h"
#include "stdlib.h"

#define SECTOR6_ADDRESS 0x8080000

uint32_t NextUpdateDataPackage = 1;
uint32_t CurrentUpdateDataPackage = 1;


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

            HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);

        }

        if(control_data_available == 1)
        {

            processControlData();

            control_data_available = 0;

        }

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




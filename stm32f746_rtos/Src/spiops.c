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


//    HAL_FLASH_Unlock();
//     FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);
//    HAL_FLASH_Lock();


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



        recieveControlData(SpiRxData);

        return HAL_OK;

    }
    else
    {

        return HAL_ERROR;

    }
}





void putControlDataResponse()
{

    putEnvironmentData();

}



void putEnvironmentData()
{

    int index = 0;

    xSemaphoreTake(spiMutexHandle, (TickType_t)1000);

        SpiTxData->header = (('E') | (('N') << 8 ));

        for(int i = 0; i < GPS_STRING_SIZE; i++)
           SpiTxData->data[i + index] = EnvironmentData->gps_string[i];

        index += GPS_STRING_SIZE;

        SpiTxData->data[index++] = EnvironmentData->step_motor1_step & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->step_motor1_step >> 8) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->step_motor1_step >> 16) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->step_motor1_step >> 24) & 0xff;

        SpiTxData->data[index++] = EnvironmentData->step_motor2_step & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->step_motor2_step >> 8) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->step_motor2_step >> 16) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->step_motor2_step >> 24) & 0xff;

        SpiTxData->data[index++] = EnvironmentData->servo_motor1_degree & 0xff;

        SpiTxData->data[index++] = EnvironmentData->servo_motor2_degree & 0xff;

        SpiTxData->data[index++] = EnvironmentData->sensor_data.temperature & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.temperature >> 8) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.temperature >> 16) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.temperature >> 24) & 0xff;

        SpiTxData->data[index++] = EnvironmentData->sensor_data.compass_degree & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.compass_degree >> 8) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.compass_degree >> 16) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.compass_degree >> 24) & 0xff;

        SpiTxData->data[index++] = EnvironmentData->sensor_data.pressure & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.pressure >> 8) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.pressure >> 16) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.pressure >> 24) & 0xff;

        SpiTxData->data[index++] = EnvironmentData->sensor_data.altitude & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.altitude >> 8) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.altitude >> 16) & 0xff;
        SpiTxData->data[index++] = (EnvironmentData->sensor_data.altitude >> 24) & 0xff;

        SpiTxData->data[index++] = EnvironmentData->sensor_data.wheather_condition & 0xff;


        SpiTxData->checksum = (('C') | (('H') << 8 ));

    xSemaphoreGive(spiMutexHandle);

}



void processControlData()
{

    xSemaphoreTake(controlMutexHandle, (TickType_t)1000);

        motor1.direction = ControlData -> step_motor1_direction;
        motor1.speed = ControlData -> step_motor1_speed;

        motor2.direction = ControlData -> step_motor2_direction;
        motor2.speed = ControlData -> step_motor2_speed;

        servo1.angle = ControlData -> servo_motor1_degree;

        servo2.angle = ControlData -> servo_motor2_degree;
        setting_enable = ControlData -> setting_enable;



        if(ControlData -> calibrate_sensor == 1)
        {
            mprintf("S\r\n");

            calibration.available = 1;

            motor1.direction = STOP;
            motor2.direction = STOP;

        }

    xSemaphoreGive(controlMutexHandle);



}


void recieveControlData(SPI_TRANSFER_FORMAT *SpiRxData)
{

    int index = 0;


    for(int i = 0; i < CONTROL_DATA_GARBAGE_SIZE; i++)
         ControlData->garbage1[i] = SpiRxData->data[i + index];

    index += CONTROL_DATA_GARBAGE_SIZE;

    ControlData->setting_enable = SpiRxData->data[index++];

    ControlData->x_position = SpiRxData->data[index++];
    ControlData->x_position |= (SpiRxData->data[index++] << 8);
    ControlData->x_position |= (SpiRxData->data[index++] << 16);
    ControlData->x_position |= (SpiRxData->data[index++] << 24);

    ControlData->y_position = SpiRxData->data[index++] & 0xff;
    ControlData->y_position |= (SpiRxData->data[index++] << 8);
    ControlData->y_position |= (SpiRxData->data[index++] << 16);
    ControlData->y_position |= (SpiRxData->data[index++] << 24);

    ControlData->z_position = SpiRxData->data[index++] & 0xff;
    ControlData->z_position |= (SpiRxData->data[index++] << 8);
    ControlData->z_position |= (SpiRxData->data[index++] << 16);
    ControlData->z_position |= (SpiRxData->data[index++] << 24);

    ControlData->step_motor1_direction = SpiRxData->data[index++];
    ControlData->step_motor2_direction = SpiRxData->data[index++];

    ControlData->servo_motor1_direction = SpiRxData->data[index++];
    ControlData->servo_motor2_direction = SpiRxData->data[index++];

    ControlData->step_motor1_speed = SpiRxData->data[index++];
    ControlData->step_motor2_speed = SpiRxData->data[index++];

    ControlData->servo_motor1_degree = SpiRxData->data[index++];
    ControlData->servo_motor1_top_degree = SpiRxData->data[index++];
    ControlData->servo_motor1_bottom_degree = SpiRxData->data[index++];

    ControlData->servo_motor2_degree = SpiRxData->data[index++];
    ControlData->servo_motor2_top_degree = SpiRxData->data[index++];
    ControlData->servo_motor2_bottom_degree = SpiRxData->data[index++];

    ControlData->calibrate_sensor = SpiRxData->data[index++];

    ControlData->step_motor1_step = SpiRxData->data[index++];
    ControlData->step_motor1_step |= (SpiRxData->data[index++] << 8);
    ControlData->step_motor1_step |= (SpiRxData->data[index++] << 16);
    ControlData->step_motor1_step |= (SpiRxData->data[index++] << 24);

    ControlData->step_motor2_step = SpiRxData->data[index++];
    ControlData->step_motor2_step |= (SpiRxData->data[index++] << 8);
    ControlData->step_motor2_step |= (SpiRxData->data[index++] << 16);
    ControlData->step_motor2_step |= (SpiRxData->data[index++] << 24);


    for(int i = 0; i < CONTROL_DATA_GARBAGE_SIZE; i++)
         ControlData->garbage1[i] = SpiRxData->data[i + index];

    index += CONTROL_DATA_GARBAGE_SIZE;


}

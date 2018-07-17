#include "sensor.h"
#include "main.h"
#include "i2c.h"

const int SENSOR_TIMEOUT = 1000;
const unsigned char WRITE_ADDRESS = 0x20;
const unsigned char READ_ADDRESS = 0x21;
const unsigned char WAKEUP_COMMAND = 0x70;
const unsigned char WHEATHER_COMMAND = 0xB3;
const unsigned char COMPASS_CALIBRATION_COMMAND = 0xe0;
const unsigned char PRESS_WRITE_COMMAND = 0xB0;
const unsigned char TEMPERATURE_WRITE_COMMAND = 0x80;
const unsigned char ALTITUDE_WRITE_COMMAND = 0xA0;
const unsigned char COMPASS_WRITE_COMMAND = 0xC0;


volatile uint8_t pressure_ready = FAIL;
volatile uint8_t altitude_ready = FAIL;
volatile uint8_t wheather_ready = FAIL;
volatile uint8_t temperature_ready = FAIL;
volatile uint8_t compass_ready = FAIL;

void sensorInit()
{
    WakeUpSensor();
}


void readAllSensors()
{

    sensorValues.pressure = readPressure();

    sensorValues.altitude = readAltitude();

    sensorValues.wheather_condition = readWheather();

    sensorValues.temperature = readTemperature();

    sensorValues.compass_degree = readCompass();

}

long readPressure()
{

    HAL_StatusTypeDef i2c_status;

    unsigned char pressure_hex[3];
    long pressure = 0;

    pressure_ready = FAIL;

    do{
    i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char *)&PRESS_WRITE_COMMAND, 1, SENSOR_TIMEOUT);
    }while(i2c_status != HAL_OK);

    if(i2c_status == HAL_OK)
    {
        HAL_Delay(200);

        i2c_status = HAL_I2C_Master_Receive(&hi2c4, READ_ADDRESS, &pressure_hex[0], 3, SENSOR_TIMEOUT);

        if(i2c_status == HAL_OK)
        {
            pressure = pressure_hex[0] << 16 |
                       pressure_hex[1] <<  8 |
                       pressure_hex[2];

             pressure_ready = OK;

            return pressure;
        }
        else
        {

            if( i2c_status == HAL_TIMEOUT)
                mprintf("PRESSURE READ:TIMOUT\r\n");
            if( i2c_status == HAL_BUSY)
                mprintf("PRESSURE READ:BUSY\r\n");
            if( i2c_status == HAL_ERROR)
                mprintf("PRESSURE READ:ERROR\r\n");

            pressure_ready = FAIL;
            return FAIL;
        }
    }
    else
    {
        mprintf("PRESSURE WRITE:FAIL\r\n");

          pressure_ready = FAIL;
        return FAIL;
    }
}

uint8_t checkPressure()
{
    uint8_t status = pressure_ready;

    if(pressure_ready == OK)
        pressure_ready = FAIL;

    return status;
}


long readAltitude()
{
    HAL_StatusTypeDef i2c_status;

    unsigned char altitude_hex[3];
    long altitude = 0;

    altitude_ready = FAIL;

    do{
         i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char *)&ALTITUDE_WRITE_COMMAND, sizeof(unsigned char), SENSOR_TIMEOUT);
    }while(i2c_status != HAL_OK);

    if(i2c_status == HAL_OK)
    {
        HAL_Delay(200);

        i2c_status = HAL_I2C_Master_Receive(&hi2c4, READ_ADDRESS, &altitude_hex[0], 3, SENSOR_TIMEOUT);

        if(i2c_status == HAL_OK)
        {
            altitude = altitude_hex[0] << 16 |
                       altitude_hex[1] <<  8 |
                       altitude_hex[2];

            if((1 << 23) & altitude) // negative altitude
            {
                altitude = altitude - 0x800000;
                altitude = altitude / 10;
                altitude = altitude * -1;
            }
            else
            {
                altitude = altitude / 10;
            }

            altitude_ready = OK;
            return altitude;
        }
        else
        {

            if( i2c_status == HAL_TIMEOUT)
                mprintf("ALTITUDE READ:TIMOUT\r\n");
            if( i2c_status == HAL_BUSY)
                mprintf("ALTITUDE READ:BUSY\r\n");
            if( i2c_status == HAL_ERROR)
                mprintf("ALTITUDE READ:ERROR\r\n");

            altitude_ready = FAIL;
            return FAIL;
        }

    }
    else
    {
        mprintf("ALTITUDE WRITE:FAIL\r\n");
        altitude_ready = FAIL;
        return FAIL;
    }

}


uint8_t checkAltitude()
{
    uint8_t status = altitude_ready;

    if(altitude_ready == OK)
        altitude_ready = FAIL;

    return status;
}


unsigned char readWheather()
{
    HAL_StatusTypeDef i2c_status;

    unsigned char wheather_status = 0;

    wheather_ready = FAIL;

    do{
    i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char *)&WHEATHER_COMMAND, 1, SENSOR_TIMEOUT);
    }while(i2c_status != HAL_OK);

    if(i2c_status == HAL_OK)
    {
        HAL_Delay(200);

        i2c_status = HAL_I2C_Master_Receive(&hi2c4, READ_ADDRESS, &wheather_status, 1, SENSOR_TIMEOUT);

        if(i2c_status == HAL_OK)
        {
            wheather_ready = OK;
            return wheather_status;
        }
        else
        {

            if( i2c_status == HAL_TIMEOUT)
                mprintf("WHEATHER READ:TIMOUT\r\n");
            if( i2c_status == HAL_BUSY)
                mprintf("WHEATHER READ:BUSY\r\n");
            if( i2c_status == HAL_ERROR)
                mprintf("WHEATHER READ:ERROR\r\n");

            wheather_ready = FAIL;
            return ERROR;
        }
    }
    else
    {
        mprintf("WHEATHER WRITE:FAIL\r\n");
        wheather_ready = FAIL;
        return ERROR;
    }
}


uint8_t checkWheather()
{
    uint8_t status = wheather_ready;

    if(wheather_ready == OK)
        wheather_ready = FAIL;

    return status;
}



int readTemperature()
{
    HAL_StatusTypeDef i2c_status;

    unsigned char temperature_hex[2];
    long temperature = 0;

    temperature_ready = FAIL;

    do{
    i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char *)&TEMPERATURE_WRITE_COMMAND, sizeof(unsigned char), SENSOR_TIMEOUT);
    }while(i2c_status != HAL_OK);

    if(i2c_status == HAL_OK)
    {
        HAL_Delay(200);

        i2c_status = HAL_I2C_Master_Receive(&hi2c4, READ_ADDRESS, &temperature_hex[0], 2, SENSOR_TIMEOUT);

        if(i2c_status == HAL_OK)
        {
            temperature = temperature_hex[0] << 8 |
                       temperature_hex[1];

            if((1 << 15) & temperature) // negative temperature
            {
                temperature = temperature - 0x8000;
                temperature = temperature / 10;
                temperature = temperature * (-1);
            }
            else
            {
                temperature = temperature / 10;
            }

            temperature_ready = OK;
            return temperature;
        }
        else
        {

            if( i2c_status == HAL_TIMEOUT)
                mprintf("TEMP READ:TIMOUT\r\n");
            if( i2c_status == HAL_BUSY)
                mprintf("TEMP READ:BUSY\r\n");
            if( i2c_status == HAL_ERROR)
                mprintf("TEMP READ:ERROR\r\n");

            temperature_ready = FAIL;
            return FAIL;
        }

    }
    else
    {
        mprintf("TEMP WRITE:FAIL\r\n");

        temperature_ready = FAIL;
        return FAIL;
    }
}


uint8_t checkTemperature()
{

    uint8_t status = temperature_ready;

    if(temperature_ready == OK)
        temperature_ready = FAIL;

    return status;
}



long readCompass()
{

    HAL_StatusTypeDef i2c_status;

    unsigned char compass_hex[2];
    long compass = 0;

    compass_ready = FAIL;

    do{
    i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char *)&COMPASS_WRITE_COMMAND, sizeof(unsigned char), SENSOR_TIMEOUT);
    }while(i2c_status != HAL_OK);

    if(i2c_status == HAL_OK)
    {
        HAL_Delay(200);

        i2c_status = HAL_I2C_Master_Receive(&hi2c4, READ_ADDRESS, &compass_hex[0], 2, SENSOR_TIMEOUT);

        if(i2c_status == HAL_OK)
        {
            compass = compass_hex[0] << 8 |
                      compass_hex[1];

            return compass;
        }
        else
        {

            if( i2c_status == HAL_TIMEOUT)
                mprintf("TEMP READ:TIMOUT\r\n");
            if( i2c_status == HAL_BUSY)
                mprintf("TEMP READ:BUSY\r\n");
            if( i2c_status == HAL_ERROR)
                mprintf("TEMP READ:ERROR\r\n");

            return FAIL;
        }
    }
    else
    {
        mprintf("TEMP WRITE:FAIL\r\n");
        return FAIL;
    }
}


uint8_t checkCompass()
{
    uint8_t status;

    if(compass_ready == OK)
        compass_ready = FAIL;

    return status;
}


int SleepSensor()
{
    return 0;
}

void WakeUpSensor()
{

    HAL_StatusTypeDef i2c_status;

    i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char *)&WAKEUP_COMMAND, 1, 1000);
    if(i2c_status == HAL_OK)
        mprintf("WAKEUP Sensor:OK\r\n");
    else if(i2c_status == HAL_BUSY)
        mprintf("WAKEUP Sensor:BUSY\r\n");
    else if(i2c_status == HAL_ERROR)
        mprintf("WAKEUP Sensor:ERROR\r\n");
    else if(i2c_status == HAL_TIMEOUT)
        mprintf("WAKEUP Sensor:TIMEOUT\r\n");

    HAL_Delay(3000);

}

void calibrateCompass()
{

    HAL_StatusTypeDef i2c_status;

    do
    {
        HAL_Delay(1000);
        i2c_status = HAL_I2C_Master_Transmit(&hi2c4, WRITE_ADDRESS, (unsigned char*)&COMPASS_CALIBRATION_COMMAND, 1, SENSOR_TIMEOUT);

        mprintf("CALIB Sensor:Triying...\n\r");

    }while(i2c_status != HAL_OK);

    HAL_Delay(10000);
    mprintf("Sensor Calib:OK\r\n");

}

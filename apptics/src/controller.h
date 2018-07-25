#ifndef Controller_H
#define Controller_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <cmath>

#include "globals.h"
#include "spicom.h"

#define SPI_TRANSFER_SIZE 120


#define FORWARD 1
#define BACKWARD 2

struct SENSOR_DATA
{
    uint32_t temperature;
    uint32_t compass_degree;
    uint32_t pressure;
    uint32_t altitude;
    uint8_t wheather_condition;

    SENSOR_DATA& operator = (unsigned char *TransferData)
    {
        temperature = TransferData[3] << 24 | TransferData[2] << 16 | TransferData[1] << 8 | TransferData[0] ;
        compass_degree = TransferData[7] << 24 | TransferData[6] << 16 | TransferData[5] << 8 | TransferData[4] ;
        pressure = TransferData[11] << 24 | TransferData[10] << 16 | TransferData[9] << 8 | TransferData[8] ;
        altitude = TransferData[15] << 24 | TransferData[14] << 16 | TransferData[13] << 8 | TransferData[12] ;
        wheather_condition = TransferData[16];

        return *this;
    }


};

struct GPS_DATA
{
    double utc_time;
    unsigned char status;
    double latitude;
    unsigned char ns_indicator;

    double longnitude;
    unsigned char we_indicator;

    double speed_over_ground;
    double course_over_ground;

    std::string date;


    GPS_DATA& operator =(std::string GpsString)
    {

        int i = 0;
        int pos;

        double degrees;
        double minutes;

        std::string gps_string = GpsString;

        std::string delimiter = ",";
        std::string token[20];


        try
        {
            while((pos = gps_string.find(delimiter)) != std::string::npos)
            {

                if(i<20)
                {
                    token[i] = gps_string.substr(0, pos);
                    gps_string.erase(0, pos + delimiter.length());
                    i++;
                }
                else
                    break;


            }

            i=0;

            if(!token[1].empty())
                utc_time = (double)std::atof(token[1].c_str());

            if(!token[2].empty())
                status = (unsigned char)*token[2].c_str();

            if(!token[3].empty())
            {
                degrees = (double)std::atof(token[3].substr(0, 2).c_str());
                minutes = (double)std::atof(token[3].substr(2, 7).c_str());
                latitude =  degrees + (minutes / 60);
            }

            if(!token[4].empty())
                ns_indicator = (unsigned char)*token[4].c_str();

            if(!token[5].empty())
            {
                degrees = (double)std::atof(token[5].substr(0, 3).c_str());
                minutes = (double)std::atof(token[5].substr(3, 7).c_str());
                longnitude = degrees + (minutes / 60);
            }

            if(!token[6].empty())
                we_indicator = (unsigned char)*token[6].c_str();

            if(!token[7].empty())
                speed_over_ground = (double)std::atof(token[7].c_str());

            if(!token[8].empty())
                course_over_ground =(double)std::atof(token[8].c_str());

            if(!token[9].empty())
                date = token[9];

        }
        catch(std::exception ex)
        {
            printAll("GPS_DATA asign Exception: ",ex.what());
        }

        return *this;
    }

};

struct SPI_RX_FORMAT
{

    GPS_DATA gps_data;
    SENSOR_DATA sensor_data;
    std::string gps_string;

    uint16_t checksum;


    SPI_RX_FORMAT& operator = (unsigned char *TransferData)
    {
        try
        {
            gps_string = std::string(&TransferData[0], &TransferData[99]);

            gps_data = gps_string;

            sensor_data = &TransferData[100];
        }
        catch(std::exception ex)
        {
            printAll("SPI_TX_FORMAT exception: ", ex.what());
        }


        return *this;
    }


};

struct SPI_TX_FORMAT
{

    uint8_t garbage1[47];
    uint32_t x_position;
    uint32_t y_position;
    uint32_t z_position;

    uint8_t step_motor1_direction;
    uint8_t step_motor2_direction;
    uint8_t step_motor3_direction;
    uint8_t step_motor4_direction;
    uint8_t servo_motor1_direction;
    uint8_t servo_motor2_direction;

    uint8_t step_motor1_speed;
    uint8_t step_motor2_speed;
    uint8_t step_motor3_speed;
    uint8_t step_motor4_speed;
    uint8_t servo_motor1_degree;
    uint8_t servo_motor2_degree;

    uint16_t checksum;

    uint8_t garbage2[48];


    SPI_TX_FORMAT& operator = (int value)
    {
        checksum = value;
        return *this;
    }

    operator int()
    {
        return checksum;
    }

    operator unsigned char *()
    {

        unsigned char *Data = new unsigned char[SPI_TRANSFER_SIZE];

        for(int i=0; i<47; i++)
        {
            garbage1[i] = 0x20;
            Data[i] = garbage1[i];
        }


        Data[48] = x_position & 0x000000ff;
        Data[49] = x_position & 0x0000ff00;
        Data[50] = x_position & 0x00ff0000;
        Data[51] = x_position & 0xff000000;

        Data[52] = y_position & 0x000000ff;
        Data[53] = y_position & 0x0000ff00;
        Data[54] = y_position & 0x00ff0000;
        Data[55] = y_position & 0xff000000;

        Data[56] = z_position & 0x000000ff;
        Data[57] = z_position & 0x0000ff00;
        Data[58] = z_position & 0x00ff0000;
        Data[59] = z_position & 0xff000000;

        Data[60] = step_motor1_direction;
        Data[61] = step_motor2_direction;
        Data[62] = step_motor3_direction;
        Data[63] = step_motor4_direction;
        Data[64] = servo_motor1_direction;
        Data[65] = servo_motor2_direction;

        Data[66] = step_motor1_speed;
        Data[67] = step_motor2_speed;
        Data[68] = step_motor3_speed;
        Data[69] = step_motor4_speed;
        Data[70] = servo_motor1_degree;
        Data[71] = servo_motor2_degree;

        Data[72] = checksum;

        for(int i=73; i<120; i++)
        {
            garbage2[i - 73] = 0x20;
            Data[i] = garbage2[i];
        }

        return Data;

    }

    SPI_TX_FORMAT& operator =(unsigned char* Data)
    {
        for(int i=0; i<47; i++)
            garbage1[i] = Data[i];

        x_position = (Data[48]) | (Data[48] << 8) | (Data[50] << 16) | (Data[51] << 24);
        y_position = (Data[52]) | (Data[53] << 8) | (Data[54] << 16) | (Data[55] << 24);
        z_position = (Data[56]) | (Data[57] << 8) | (Data[58] << 16) | (Data[59] << 24);

        step_motor1_direction = Data[60];
        step_motor2_direction = Data[61];
        step_motor3_direction = Data[62];
        step_motor4_direction = Data[63];
        servo_motor1_direction = Data[64];
        servo_motor2_direction = Data[65];

        step_motor1_speed = Data[66];
        step_motor2_speed = Data[67];
        step_motor3_speed = Data[68];
        step_motor4_speed = Data[69];
        servo_motor1_degree = Data[70];
        servo_motor2_degree = Data[71];

        checksum = Data[72];

        for(int i=73; i<120; i++)
            garbage2[i - 73] = Data[i];


        return *this;


    }

    void clear()
    {
        step_motor1_direction = 0;
        step_motor2_direction = 0;
        step_motor3_direction = 0;
        step_motor4_direction = 0;

        step_motor1_speed = 0;
        step_motor2_speed = 0;
        step_motor3_speed = 0;
        step_motor4_speed = 0;

        servo_motor1_degree = 0;
        servo_motor1_degree = 0;

        checksum = 0;
    }

};

class Controller
{
public:

    enum class Controller_Status
    {
        time_out,
        error,
        ok

    }Status;

    Controller();
    ~Controller();

    Controller_Status zoomInCamera();
    Controller_Status zoomOutCamera();

    Controller_Status driveMotorLeft();
    Controller_Status driveMotorRight();
    Controller_Status driveMotorDown();
    Controller_Status driveMotorUp();

    Controller_Status setControlData(SPI_TX_FORMAT Data);

    SPI_RX_FORMAT getStmEnvironment();


private:

    volatile int gmDataReady = 0;

    SPI_RX_FORMAT gmStmEnvironmentData;
    SPI_TX_FORMAT gmBPIControlData;

    SpiCom gmSpi;

    std::mutex gmMutex;

    void communicationThread();


};

#endif // Controller_H

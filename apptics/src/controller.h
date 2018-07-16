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


    GPS_DATA& operator =(const std::string& GpsString)
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

            while ((pos = gps_string.find(delimiter)) != std::string::npos)
            {

                token[i] = gps_string.substr(0, pos);
                gps_string.erase(0, pos + delimiter.length());
                i++;

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
            printAll("GPS_DATA asign: ",ex.what());
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
        gps_string = std::string(&TransferData[0], &TransferData[99]);

        gps_data = gps_string;

        sensor_data = &TransferData[100];

        return *this;
    }


};

struct SPI_TX_FORMAT
{

    uint8_t garbage1[45];
    uint32_t x_position;
    uint32_t y_position;
    uint32_t z_position;

    uint8_t step_motor1_direction;
    uint8_t step_motor2_direction;
    uint8_t step_motor3_direction;
    uint8_t step_motor4_direction;
    uint8_t servo_motor1_direction;
    uint8_t servo_motor2_direction;

    uint8_t step_motor1_degree;
    uint8_t step_motor2_degree;
    uint8_t step_motor3_degree;
    uint8_t step_motor4_degree;
    uint8_t servo_motor1_degree;
    uint8_t servo_motor2_degree;

    uint16_t checksum;

    uint8_t garbage2[46];

};

class Controller
{
public:

    enum class Bpi_Status
    {
        time_out,
        error,
        ok
    }Status;

    Controller();
    ~Controller();
    Bpi_Status setControlData(const SPI_TX_FORMAT& Data);
    SPI_RX_FORMAT getStmEnvironment();


private:

    SPI_RX_FORMAT gmStmEnvironmentData;
    SPI_TX_FORMAT gmBPIControlData;

    SpiCom gmSpi;

    std::mutex gmMutex;

    void communicationThread();


};

#endif // Controller_H

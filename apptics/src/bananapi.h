#ifndef BANANAPI_H
#define BANANAPI_H

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
#include "globals.h"
#include <cmath>

#include "spicom.h"

#define SPI_TRANSFER_SIZE 120

struct SENSOR_DATA
{
    uint32_t temperature;
    uint32_t compass_degree;
    uint32_t pressure;
    uint32_t altitude;
    uint8_t wheather_condition;
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

};

struct SPI_RX_FORMAT
{

    GPS_DATA gps_data;
    SENSOR_DATA sensor_data;
    double degrees;
    double minutes;

    uint16_t checksum;


    SPI_RX_FORMAT& operator = (unsigned char *TransferData)
    {
        std::string gps_string(&TransferData[0], &TransferData[99]);
        int i = 0;
        int pos;

//        std::string gps_string = "$GPRMC,053740.000,A,2503.6319,N,12136.0099,E,2.69,79.65,100106,,,A*53";
        std::string delimiter = ",";
        std::string token[20];

        while ((pos = gps_string.find(delimiter)) != std::string::npos)
        {

            token[i] = gps_string.substr(0, pos);
            gps_string.erase(0, pos + delimiter.length());
            i++;

        }

        i=0;

        gps_data.utc_time = (double)std::atof(token[1].c_str());

        gps_data.status = (unsigned char)*token[2].c_str();

        degrees = (double)std::atof(token[3].substr(0, 1).c_str());
        minutes = (double)std::atof(token[3].substr(2, 6).c_str());
        gps_data.latitude =  degrees + (minutes / 60);

        gps_data.ns_indicator = (unsigned char)*token[4].c_str();

        degrees = (double)std::atof(token[5].substr(0, 2).c_str());
        minutes = (double)std::atof(token[5].substr(3, 7).c_str());
        gps_data.longnitude = degrees + (minutes / 60);

        gps_data.we_indicator = (unsigned char)*token[6].c_str();

        gps_data.speed_over_ground = (double)std::atof(token[7].c_str());

        gps_data.course_over_ground =(double)std::atof(token[8].c_str());

        gps_data.date = token[9];

//        sensor_data = (SENSOR_DATA) &TransferData[100];

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

class BananaPi
{
public:

    enum class Bpi_Status
    {
        time_out,
        error,
        ok
    }Status;

    BananaPi();
    ~BananaPi();
    Bpi_Status setControlData(const SPI_TX_FORMAT& Data);
    Bpi_Status getStmEnvironment(SPI_RX_FORMAT Data);


private:

    SPI_RX_FORMAT gmStmEnvironmentData;
    SPI_TX_FORMAT gmBPIControlData;

    SpiCom gmSpi;

    std::mutex gmMutex;

    void communicationThread();


};

#endif // BANANAPI_H

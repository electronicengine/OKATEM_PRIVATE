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
    SENSOR_DATA *sensor_data;
    std::string gps_string;
    double degrees;
    double minutes;

    uint16_t checksum;


    SPI_RX_FORMAT& operator = (unsigned char *TransferData)
    {
        gps_string = std::string(&TransferData[0], &TransferData[99]);
        int i = 0;
        int pos;

//        std::string gps_string = "$GPRMC,053740.000,A,2503.6319,N,12136.0099,E,2.69,79.65,100106,,,A*53";
//        std::string delimiter = ",";
//        std::string token[20];


//        try
//        {

//            while ((pos = gps_string.find(delimiter)) != std::string::npos)
//            {

//                token[i] = gps_string.substr(0, pos);
//                gps_string.erase(0, pos + delimiter.length());
//                i++;

//            }

//            i=0;

//            if(!token[1].empty())
//                gps_data.utc_time = (double)std::atof(token[1].c_str());

//            if(!token[2].empty())
//                gps_data.status = (unsigned char)*token[2].c_str();

//            if(!token[3].empty())
//            {
//                degrees = (double)std::atof(token[3].substr(0, 2).c_str());
//                minutes = (double)std::atof(token[3].substr(2, 7).c_str());
//                gps_data.latitude =  degrees + (minutes / 60);
//            }

//            if(!token[4].empty())
//                gps_data.ns_indicator = (unsigned char)*token[4].c_str();

//            if(!token[5].empty())
//            {
//                degrees = (double)std::atof(token[5].substr(0, 3).c_str());
//                minutes = (double)std::atof(token[5].substr(3, 7).c_str());
//                gps_data.longnitude = degrees + (minutes / 60);
//            }

//            if(!token[6].empty())
//                gps_data.we_indicator = (unsigned char)*token[6].c_str();

//            if(!token[7].empty())
//                gps_data.speed_over_ground = (double)std::atof(token[7].c_str());

//            if(!token[8].empty())
//                gps_data.course_over_ground =(double)std::atof(token[8].c_str());

//            if(!token[9].empty())
//                gps_data.date = token[9];

//        }
//        catch(std::exception ex)
//        {
//            printAll(ex.what());
//        }


        sensor_data = reinterpret_cast<SENSOR_DATA *>(&TransferData[100]);


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

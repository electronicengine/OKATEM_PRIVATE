#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "lasertracker.h"
#include "globals.h"
#include <sstream>
#include "lorawan.h"
#include "spicom.h"
#include "bananapi.h"
#include "sfpmonitor.h"
#include <string>
#include <string.h>
#include <time.h>


struct LORA_DATA
{
    int sensor_temperature;
    int sensor_altitude;
    int sensor_pressure;
    int sensor_wheather_condition;
    int sensor_compass_degree;
    bool sfp_status;

}LoraData;

void loraCallBackFunction(std::string CommingData);


SPI_RX_FORMAT stm_data;
SFP_DATA sfp_data;
std::string lora_data;
int gps_char_pos;

//hello

LoraWan lora;
BananaPi bpi;
SfpMonitor sfp_monitor;
LaserTracker tracker(0);


int main(int argc, char* argv[])
{


//    tracker.runTracking();
    sleep(1);

    stm_data = bpi.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    lora.setLoraData(sfp_data, stm_data);

    lora.sendBeacon();

    sleep(1);

    lora.listen();

    sleep(3);

    while(1)
    {

        stm_data = bpi.getStmEnvironment();
        sfp_data = sfp_monitor.getValues();



        lora.setLoraData(sfp_data, stm_data);

        printAll("Environment Data: ");

        std::cout << "Gps Data:  " <<  stm_data.gps_string << std::endl;
        printAll("Temperature: ", (int)stm_data.sensor_data->temperature,
                 " - Altitude: ", (int)stm_data.sensor_data->altitude, " - Pressure: ", (int)stm_data.sensor_data->pressure,
                 " - Compass: ", (int)stm_data.sensor_data->compass_degree, " - Wheather: ", (int)stm_data.sensor_data->wheather_condition,
                 " - SFP Status: ", (sfp_data.status == 1) ? "Connected" : "Disconnected");
        printAll("\n\n\n");

        sleep(4);

    }

    return 0;

}



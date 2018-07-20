#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>

//#include <ncurses.h>

#include "lasertracker.h"
#include "globals.h"
#include "lorawan.h"
#include "spicom.h"
#include "controller.h"
#include "sfpmonitor.h"
#include "udpsocket.h"



clock_t now = 0;
clock_t last = 0;

SPI_RX_FORMAT stm_data;
SPI_RX_FORMAT lora_stm_data;

SPI_TX_FORMAT control_data;

SFP_DATA sfp_data;
SFP_DATA lora_sfp_data;

LoraWan lora;
Controller controller;
SfpMonitor sfp_monitor;
LaserTracker tracker(0);
UdpSocket udp_socket;

void safeLog();


int main(int argc, char* argv[])
{


    int a;
    tracker.runTracking();

    stm_data = controller.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    lora.setLoraData(sfp_data, stm_data);

    lora.sendBeacon();

    lora.listen();

    while(1)
    {


        stm_data = controller.getStmEnvironment();
        sfp_data = sfp_monitor.getValues();

        lora.setLoraData(sfp_data, stm_data);

        lora.getLoraData(lora_sfp_data, lora_stm_data);

        control_data = udp_socket.getSocketData();

        if(control_data != FAIL )
        {
            controller.setControlData(control_data);
            control_data.clear();
        }


        now = clock();

        if(now - last > 5000000)
        {
            safeLog();
            last = now;
        }



    }

    return 0;

}


void safeLog()
{

    printAll("Environment Data: ");

    std::cout << "Gps Data:  " <<  stm_data.gps_string << std::endl;
    printAll("Temperature: ", (int)stm_data.sensor_data.temperature,
             " - Altitude: ", (int)stm_data.sensor_data.altitude, " - Pressure: ", (int)stm_data.sensor_data.pressure,
             " - Compass: ", (int)stm_data.sensor_data.compass_degree, " - Wheather: ", (int)stm_data.sensor_data.wheather_condition,
             " - SFP Status: ",(sfp_data.status == 1) ? "Connected" : "Disconected");
    printAll("\n\n\n");

    printAll("Tracker Diagonal Rate: ", tracker.getDiagonalRate());
    printAll("Tracker Edge Rate: ", tracker.getEdgeRate());
    printAll("\n\n\n");

    printAll("Lora Data: ");
    printAll("Temperature: ", (int)lora_stm_data.sensor_data.temperature,
    " - Altitude: ", (int)lora_stm_data.sensor_data.altitude,
    " - Pressure: ", (int)lora_stm_data.sensor_data.pressure,
    " - Wheather_condition: ", (int)lora_stm_data.sensor_data.wheather_condition,
    " - Compass_degree: ", (int)lora_stm_data.sensor_data.compass_degree,
    " - Sfp status: ", (lora_sfp_data.status == 1) ? "Connected" : "Disconected");



    printAll("\n\n\n");


}



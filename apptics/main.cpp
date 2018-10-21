#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <sys/types.h>
#include <sys/sysinfo.h>

#include "lasertracker.h"
#include "globals.h"
#include "lorawan.h"
#include "spicom.h"
#include "controller.h"
#include "sfpmonitor.h"
#include "udpsocket.h"
#include "queue.h"
#include "lcdhmi.h"
#include "json.h"


std::map<const std::string, bool> CheckList;


clock_t now = 0;
clock_t last = 0;


Queue<UPDATE_FILE_FORMAT> file_queue;

MOTOR_POSITION_FORMAT motor_positions;

ENVIRONMENT_DATA_FORMAT stm_data;
ENVIRONMENT_DATA_FORMAT lora_stm_data;


CONTROL_DATA_FORMAT udp_control_data;
CONTROL_DATA_FORMAT lcd_control_data;
UPDATE_FILE_FORMAT update_file;


SFP_DATA_FORMAT sfp_data;
SFP_DATA_FORMAT lora_sfp_data;


LoraWan lora;
Controller controller;
SfpMonitor sfp_monitor;
LaserTracker tracker(0);
UdpSocket udp_controller_socket;
LcdHMI lcd_hmi;
Json json;


void safeLog();



int main()
{

    Status update_file_status = Status::ok;

    json.loadMotorPositions(lcd_control_data);
    json.loadMotorPositions(udp_control_data);

    lcd_hmi.setMotorPositions(lcd_control_data);

    tracker.runTracking();

    stm_data = controller.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    lora.setLoraData(sfp_data, stm_data);

    lora.sendBeacon();

    lora.listen();

    sleep(1);

    udp_controller_socket.openPort(CONTROLLER_PORT, LISTENING_MODE);

    while(1)
    {

        stm_data = controller.getStmEnvironment();

        sfp_data = sfp_monitor.getValues();

        json.saveEnvironmentData(stm_data, sfp_data); //

        lora.setLoraData(sfp_data, stm_data);

        lcd_hmi.setHCMData(sfp_data, stm_data);

        lora.getLoraData(lora_sfp_data, lora_stm_data);

        json.saveLoraData(lora_stm_data, lora_sfp_data);  //

        udp_control_data = udp_controller_socket.getSocketControlData();

        lcd_control_data = lcd_hmi.getHCMControlData();

        if(update_file_status == Status::ok)
            update_file = udp_controller_socket.getSocketUpdateData();

        if(update_file.is_available == true)
        {
            update_file_status = controller.setUpdateData(update_file);
        }
        else if(udp_control_data == true)
        {
            controller.setControlData(udp_control_data);
            json.saveMotorPositions(udp_control_data);
        }
        else if(lcd_control_data == true)
        {
            controller.setControlData(lcd_control_data);
            json.saveMotorPositions(lcd_control_data);
        }

        udp_control_data.clear();

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


    printAll("Environment Data: ", "\n", "Gps:  ", stm_data.gps_string.substr(0,stm_data.gps_string.find('*')), "\n"
             " - Temperature: ", (int)stm_data.sensor_data.temperature,
             " - Altitude: ", (int)stm_data.sensor_data.altitude, " - Pressure: ", (int)stm_data.sensor_data.pressure,
             " - Compass: ", (int)stm_data.sensor_data.compass_degree, " - Wheather: ", (int)stm_data.sensor_data.wheather_condition,
             " - SFP Status: ",(sfp_data.status == 1) ? "Connected" : "Disconnected",
             " - SFP Tx power: ", sfp_data.tx_power,
             " - SFP Rx power: ", sfp_data.rx_power);
    printAll("\n\n\n");

    printAll("Tracker Diagonal Rate: ", tracker.getDiagonalRate(), " - ", "Tracker Edge Rate: ", tracker.getEdgeRate());
    printAll("\n\n\n");

        printAll("Lora  Data: ", "\n", "Gps:  ", lora_stm_data.gps_string.substr(0,lora_stm_data.gps_string.find('*')),
        " - Temperature: ", (int)lora_stm_data.sensor_data.temperature,
        " - Altitude: ", (int)lora_stm_data.sensor_data.altitude,
        " - Pressure: ", (int)lora_stm_data.sensor_data.pressure,
        " - Compass: ", (int)lora_stm_data.sensor_data.compass_degree,
        " - Wheather: ", (int)lora_stm_data.sensor_data.wheather_condition,
        " - Sfp status: ", (lora_sfp_data.status == 1) ? "Connected" : "Disconnected");


    printAll("\n\n\n");



}








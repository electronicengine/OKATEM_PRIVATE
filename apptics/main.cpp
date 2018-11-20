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

std::string stream_ip;
int stream_port;

Queue<UPDATE_FILE_FORMAT> file_queue;

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


Status update_file_seq_is_sent  = Status::ok;


void safeLog();
void initUdpSocket();
void initConfig();
void initCamera();
void initLora();

void getEnvironment();
void shareEnvironment();

int checkIfUdpData();
int checkIfLcdData();

int main()
{

    int ret;

    initConfig();
    initCamera();
    initLora();
    initUdpSocket();

    while(1)
    {

        getEnvironment();
        shareEnvironment();

        ret = checkIfUdpData();

        if(ret != SUCCESS)
            checkIfLcdData();


        now = clock();

        if(now - last > 2000000)
        {
            safeLog();
            last = now;
        }


    }



    return 0;

}



int checkIfLcdData()
{

    lcd_control_data = lcd_hmi.getHCMControlData();

   if(lcd_control_data == true)
    {
        controller.setControlData(lcd_control_data);
        json.saveMotorPositions(lcd_control_data);
    }
}



int checkIfUdpData()
{

    udp_control_data = udp_controller_socket.getSocketControlData();

    if(update_file_seq_is_sent == Status::ok)
        update_file = udp_controller_socket.getSocketUpdateData();

    if(update_file.is_available == true)
    {
        update_file_seq_is_sent = controller.setUpdateData(update_file);
    }
    else if(udp_control_data.is_available == true)
    {
        controller.setControlData(udp_control_data);

        json.saveMotorPositions(udp_control_data);
    }

    udp_control_data.clear();

}



void shareEnvironment()
{

    json.saveEnvironmentData(stm_data, sfp_data);

    lora.setLoraData(sfp_data, stm_data);

    lcd_hmi.setHCMData(sfp_data, stm_data);

    json.saveLoraData(lora_stm_data, lora_sfp_data);

}



void getEnvironment()
{
    stm_data = controller.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    lora.getLoraData(lora_sfp_data, lora_stm_data);
}



void initUdpSocket()
{
    udp_controller_socket.openPort(stream_ip, CONTROLLER_PORT, LISTENING_MODE);
    udp_controller_socket.saveInformationData(udp_control_data, stm_data ,sfp_data);
}



void initLora()
{

    Status status;

    status = lora.init();


    stm_data = controller.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    if(lora.init() == Status::ok)
    {

        lora.setLoraData(sfp_data, stm_data);

        lora.sendBeacon();

        lora.listen();

    }
    else
    {
        printAll("Lora Init Error!!");
    }

}



void initCamera()
{
    tracker.runTracking(stream_ip, stream_port);
}



void initConfig()
{

    json.loadMotorPositions(lcd_control_data);
    json.loadMotorPositions(udp_control_data);

    json.loadStreamInfo(stream_ip, stream_port);

    lcd_hmi.setInitialMotorPositions(lcd_control_data);


}



void safeLog()
{

    CONTROL_DATA_FORMAT control_data;

    json.loadMotorPositions(control_data);

    udp_controller_socket.saveInformationData(control_data, stm_data ,sfp_data);

//    printAll("Environment Data: ", "\n", "Gps:  ", stm_data.gps_string.substr(0,stm_data.gps_string.find('*')), "\n"
//             " - Temperature: ", (int)stm_data.sensor_data.temperature,
//             " - Altitude: ", (int)stm_data.sensor_data.altitude, " - Pressure: ", (int)stm_data.sensor_data.pressure,
//             " - Compass: ", (int)stm_data.sensor_data.compass_degree, " - Wheather: ", (int)stm_data.sensor_data.wheather_condition,
//             " - SFP Status: ",(sfp_data.status == 1) ? "Connected" : "Disconnected",
//             " - SFP Tx power: ", sfp_data.tx_power,
//             " - SFP Rx power: ", sfp_data.rx_power);
//    printAll("\n\n\n");

//    printAll("Tracker Diagonal Rate: ", tracker.getDiagonalRate(), " - ", "Tracker Edge Rate: ", tracker.getEdgeRate());
//    printAll("\n\n\n");

//        printAll("Lora  Data: ", "\n", "Gps:  ", lora_stm_data.gps_string.substr(0,lora_stm_data.gps_string.find('*')),
//        " - Temperature: ", (int)lora_stm_data.sensor_data.temperature,
//        " - Altitude: ", (int)lora_stm_data.sensor_data.altitude,
//        " - Pressure: ", (int)lora_stm_data.sensor_data.pressure,
//        " - Compass: ", (int)lora_stm_data.sensor_data.compass_degree,
//        " - Wheather: ", (int)lora_stm_data.sensor_data.wheather_condition,
//        " - Sfp status: ", (lora_sfp_data.status == 1) ? "Connected" : "Disconnected");


//    printAll("\n\n\n");



}








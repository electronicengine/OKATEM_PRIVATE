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
#include "stmdriver.h"
#include "sfpmonitor.h"
#include "udpsocket.h"
#include "queue.h"
#include "lcdhmi.h"
#include "json.h"
#include <linux/videodev2.h>
#include "cameradriver.h"

std::map<const std::string, bool> CheckList;

clock_t now = 0;
clock_t last = 0;

REMOTEMACHINE_INFORMATIONS remote_machine_informations;
Queue<UPDATE_FILE_FORMAT> file_queue;

ENVIRONMENT_DATA_FORMAT stm_data;
ENVIRONMENT_DATA_FORMAT lora_stm_data;

CONTROL_DATA_FORMAT udp_control_data;
CONTROL_DATA_FORMAT lcd_control_data;
UPDATE_FILE_FORMAT update_file;
CAMERA_SETTINGS_FORMAT camera_settings;

SFP_DATA_FORMAT sfp_data;
SFP_DATA_FORMAT lora_sfp_data;

LoraWan lora;
StmDriver stm_driver;
SfpMonitor sfp_monitor;
LaserTracker tracker;
UdpSocket udp_controller_socket;
LcdHMI lcd_hmi;
Json json;
CameraDriver camera_driver;

Status update_file_seq_is_sent  = Status::ok;

void safeLog();

int init();
int initUdpControlSocket();
int initConfig();
int initCamera();
int initLora();
int initController();
int initSfpMonitor();
int initLcd();
int initCameraController();

int getEnvironment();

void shareEnvironment();


int checkIfUdpDataAvaliable();
int checkIfLcdDataAvaliable();
int checkUdpCalibrationValues(CONTROL_DATA_FORMAT &ControlData);


int main()
{

    int ret;

    ret = init();

    if(ret == FAIL)
    {
        printAll("Device Initialize has been Faild. Process will terminate");
        return 0;
    }

    while(1)
    {

        getEnvironment();
        shareEnvironment();

        ret = checkIfUdpDataAvaliable();

        if(ret != SUCCESS)
            checkIfLcdDataAvaliable();

        now = clock();

        if(now - last > 2000000)
        {
            safeLog();
            last = now;
        }

    }

    return 0;

}



int init()
{

    int ret;

    ret = json.init();

    if(ret == FAIL)
        return FAIL;

    ret = initConfig();

    if(ret == FAIL)
        return FAIL;

    ret = initLora();

    if(ret == FAIL)
        return FAIL;

    ret = initController();

    if(ret == FAIL)
        return FAIL;

    ret = initSfpMonitor();

    if(ret == FAIL)
        return FAIL;

    ret = initCamera();
    if(ret == FAIL)
        return FAIL;

    ret = initUdpControlSocket();
    if(ret == FAIL)
        return FAIL;

    ret = initLcd();
    if(ret == FAIL)
        return FAIL;

    ret = initCameraController();
    if(ret == FAIL)
        return FAIL;

    return SUCCESS;

}



int initCameraController()
{
    return camera_driver.init();
}



int initLcd()
{
    return lcd_hmi.init();
}



int initSfpMonitor()
{
    return sfp_monitor.init();
}



int initController()
{
    return stm_driver.init();
}



int checkIfLcdDataAvaliable()
{

    lcd_control_data = lcd_hmi.getHCMControlData();

   if(lcd_control_data == true)
    {
        stm_driver.setControlData(lcd_control_data);
    }

}



int checkIfUdpDataAvaliable()
{

    Status status;

    udp_control_data = udp_controller_socket.getSocketControlData();

    if(update_file_seq_is_sent == Status::ok)
        update_file = udp_controller_socket.getSocketUpdateData();

    camera_settings = udp_controller_socket.getCameraSettings();


    if(update_file.is_available == true)
    {

        update_file_seq_is_sent = stm_driver.setUpdateData(update_file);

        if(update_file_seq_is_sent == Status::ok)
        {
            UDP_DATA_FORMAT feed_back_data;

            feed_back_data.header = UDP_DATA_FORMAT::FEEDBACK_DATA;
            udp_controller_socket.sendData(feed_back_data);
        }

    }
    else if(udp_control_data.is_available == true)
    {

        if(checkUdpCalibrationValues(udp_control_data) != SUCCESS)
            stm_driver.setControlData(udp_control_data);

    }
    else if(camera_settings.available == true)
    {
        if(camera_settings.write_enable == 0)
        {
            std::cout << "camera settings request"<< std::endl;

            int ret = 0;

            camera_settings = camera_driver.getCameraControls();
            camera_settings.write_enable = 1;

            printAll("brightness: ", std::to_string(camera_settings.brighness));
            printAll("contrast: ", std::to_string(camera_settings.contrast));
            printAll("saturation: ", std::to_string(camera_settings.saturation));
            printAll("hue: ", std::to_string(camera_settings.hue));
            printAll("exposure: ", std::to_string(camera_settings.exposure));
            printAll("auto_exposure: ", std::to_string(camera_settings.auto_exposure));
            printAll("gain: ", std::to_string(camera_settings.gain));
            printAll("auto_gain: ", std::to_string(camera_settings.auto_gain));
            printAll("horizontal_flip: ", std::to_string(camera_settings.horizontal_flip));
            printAll("vertical_flip: ", std::to_string(camera_settings.vertical_flip));
            printAll("power_frequency: ", std::to_string(camera_settings.power_frequency));
            printAll("sharpness: ", std::to_string(camera_settings.sharpness));

            ret = udp_controller_socket.sendData(camera_settings);

            if(ret == FAIL)
                printAll("Camera Setting Information can not be sent!");

        }
        else if(camera_settings.write_enable == 0xff)
        {
            int ret;

            ret = camera_driver.setCameraControls(camera_settings);
        }

    }

    udp_control_data.clear();

}



int checkUdpCalibrationValues(CONTROL_DATA_FORMAT &ControlData)
{
    if(ControlData.setting_enable == 0xff)
    {

        MOTOR_INFORMATIONS calibration_values;

        printAll("Calibration Values are setting...");

        calibration_values = ControlData;
        json.saveMotorPositions(calibration_values);
        stm_driver.setMotorCalibrationValues(calibration_values);

        std::cout << "step_motor1_step: " << std::to_string(calibration_values.step_motor1_position) << std::endl;
        std::cout << "step_motor1_max_step: " << std::to_string(calibration_values.step_motor1_max_step) << std::endl;

        std::cout << "step_motor2_step: " << std::to_string(calibration_values.step_motor2_position) << std::endl;
        std::cout << "step_motor2_max_step: " << std::to_string(calibration_values.step_motor2_max_step) << std::endl;

        std::cout << "servo_motor1_degree: " << std::to_string(calibration_values.servo_motor1_degree) << std::endl;
        std::cout << "servo_motor2_degree: " << std::to_string(calibration_values.servo_motor2_degree) << std::endl;

        std::cout << "servo_motor1_bottom_degree: " << std::to_string(calibration_values.servo_motor1_bottom_degree) << std::endl;
        std::cout << "servo_motor1_top_degree: " << std::to_string(calibration_values.servo_motor1_top_degree) << std::endl;

        std::cout << "servo_motor2_bottom_degree: " << std::to_string(calibration_values.servo_motor2_bottom_degree) << std::endl;
        std::cout << "servo_motor2_top_degree: " << std::to_string(calibration_values.servo_motor2_top_degree) << std::endl;

        stm_driver.resetStm();

        ControlData.clear();

        return SUCCESS;

    }
    else
        return FAIL;

}

void shareEnvironment()
{

    json.saveEnvironmentData(stm_data, sfp_data);

    lora.setLoraData(sfp_data, stm_data);

    lcd_hmi.setHCMData(sfp_data, stm_data);

    json.saveLoraData(lora_stm_data, lora_sfp_data);

}



int getEnvironment()
{

    int ret;

    stm_data = stm_driver.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    lora.getLoraData(lora_sfp_data, lora_stm_data);

    return ret;
}



int initUdpControlSocket()
{

    int ret;

    udp_controller_socket.init(remote_machine_informations.stream_ip, remote_machine_informations.control_port);

    if(ret == SUCCESS)
    {
        udp_controller_socket.listen();
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }

}



int initLora()
{


    int ret;

    ret = lora.init();

    if(ret == SUCCESS)
    {

        stm_data = stm_driver.getStmEnvironment();
        sfp_data = sfp_monitor.getValues();

        lora.setLoraData(sfp_data, stm_data);

        lora.sendBeacon();

        lora.listen();

        return SUCCESS;

    }
    else
    {
        printAll("Lora Init Error!!");

        return FAIL;
    }

}



int initCamera()
{

    int ret;

    ret = tracker.init(0);

    if(ret == SUCCESS)
    {

        tracker.runTracking(remote_machine_informations.stream_ip, remote_machine_informations.stream_port);

        return SUCCESS;
    }
    else
    {
        return FAIL;
    }

}



int initConfig()
{

    int ret;

    MOTOR_INFORMATIONS motor_informations;

    ret = json.loadMotorPositions(motor_informations);

    if(ret == FAIL)
        return FAIL;

    ret = json.loadStreamInfo(remote_machine_informations);

    if(ret == FAIL)
        return FAIL;

    stm_driver.setMotorCalibrationValues(motor_informations);

    lcd_control_data = motor_informations;
    udp_control_data = motor_informations;

    lcd_hmi.setInitialMotorPositions(lcd_control_data);
    udp_controller_socket.setInitialMotorPositions(udp_control_data);

    return SUCCESS;

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


#ifndef JSON_H
#define JSON_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <numeric>
#include "globals.h"
#include <memory>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>



class Json
{

public:

    enum FileTypes
    {
        RemoteMachineFileInfo,
        LoraInfo,
        SensorInfo,
        MotorInfo
    };


    Json();
    ~Json();

    int init();

    void saveStreamInfo(const REMOTEMACHINE_INFORMATIONS& JsonData);
    void saveBoardInfo(const JSON_SENSOR_INFORMATIONS& JsonData);
    void saveMotorInfo(const MOTOR_INFORMATIONS &MotorInfo);

    REMOTEMACHINE_INFORMATIONS loadStreamInfo();
    JSON_SENSOR_INFORMATIONS loadSensorInfo();
    MOTOR_INFORMATIONS loadMotorInfo();


private:

    REMOTEMACHINE_INFORMATIONS gmRemoteMachineInformations;
    MOTOR_INFORMATIONS gmMotorInformations;
    JSON_SENSOR_INFORMATIONS gmJsonSensorInformations;

    const std::vector<std::string> FILES{"/var/www/html/remotemachine.json",
                                         "/var/www/html/lora.json",
                                         "/var/www/html/sensors.json",
                                         "/var/www/html/motors.json"};

    const std::vector<std::string> FILES_BACKUP{"/var/www/html/remotemachine_backup.json",
                                                "/var/www/html/lora_backup.json",
                                                "/var/www/html/sensors_backup.json",
                                                "/var/www/html/motors_backup.json"};

    std::mutex gmMutex;

    void writeFile(const std::string &Content, const std::string &File);
    std::string readFile(const std::string &File);

    void readStreamInfo(REMOTEMACHINE_INFORMATIONS &ControlData);
    void readSensorInfo(JSON_SENSOR_INFORMATIONS &ControlData);
    void readMotorInfo(MOTOR_INFORMATIONS &ControlData);


    void getPhysicalSourceUsage(float &MemUsage, float &CpuUsage);
    std::vector<size_t> getCpuTick();
    bool getCpuTime(size_t &idle_time, size_t &total_time);
    float getCpuUsage();

};

#endif // JSON_H

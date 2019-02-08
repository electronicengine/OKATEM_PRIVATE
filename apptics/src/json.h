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
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <fstream>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <numeric>
#include "globals.h"
#include <memory>




class Json
{

public:

    Json();
    Json(int Mode);
    ~Json();

    int init();

    void saveEnvironmentData(ENVIRONMENT_DATA_FORMAT &StmData, SFP_DATA_FORMAT &SfpData);
    void saveLoraData(ENVIRONMENT_DATA_FORMAT &LoraStmData, SFP_DATA_FORMAT &LoraSfpData);

    template <typename T>
    int loadMotorPositions(T &ControlData)
    {
        MOTOR_INFORMATIONS info;

        info = ControlData;

        loadMotorPositions(info);

        ControlData = info;

    }


    template <typename T>
    int saveMotorPositions(T &ControlData)
    {

    }

    int loadMotorPositions(MOTOR_INFORMATIONS &ControlData);
    void saveMotorPositions(MOTOR_INFORMATIONS &ControlData);


    int loadStreamInfo(REMOTEMACHINE_INFORMATIONS &RemoteMachine);

private:

    ENVIRONMENT_DATA_FORMAT gmStmData;
    ENVIRONMENT_DATA_FORMAT gmLoraStmData;

    SFP_DATA_FORMAT gmSfpData;
    SFP_DATA_FORMAT gmLoraSfpData;

    MOTOR_INFORMATIONS gmMotorInformations;
    REMOTEMACHINE_INFORMATIONS gmRemoteMachineInformations;

    std::mutex gmMutex;

    void writeJson();
    int writeFile(const std::string &Content);
    std::string readFile();


    void getPhysicalSourceUsage(float &MemUsage, float &CpuUsage);
    std::vector<size_t> getCpuTick();
    bool getCpuTime(size_t &idle_time, size_t &total_time);
    float getCpuUsage();

};

#endif // JSON_H

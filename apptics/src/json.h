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



class Json
{

public:

    Json();
    Json(int Mode);
    ~Json();


    void saveEnvironmentData(ENVIRONMENT_DATA_FORMAT &StmData, SFP_DATA_FORMAT &SfpData);
    void saveLoraData(ENVIRONMENT_DATA_FORMAT &LoraStmData, SFP_DATA_FORMAT &LoraSfpData);

    void loadMotorPositions(CONTROL_DATA_FORMAT &ControlData);
    void saveMotorPositions(CONTROL_DATA_FORMAT &ControlData);

    void loadStreamInfo(std::string &StreamIp, int &StreamPort);

private:

//    rapidjson::StringBuffer gmStringBuffer;
//    rapidjson::Writer<rapidjson::StringBuffer> *gmWriter;

    ENVIRONMENT_DATA_FORMAT gmStmData;
    ENVIRONMENT_DATA_FORMAT gmLoraStmData;

    SFP_DATA_FORMAT gmSfpData;
    SFP_DATA_FORMAT gmLoraSfpData;


    CONTROL_DATA_FORMAT gmControlData;

    uint8_t gmServoMotor2Degree;
    uint8_t gmServoMotor1Degree;

    int gmStepMotor1Position;
    int gmStepMotor2Position;

    std::string gmStreamIp;
    int gmStreamPort;

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
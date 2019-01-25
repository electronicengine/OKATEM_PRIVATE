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


struct MOTOR_INFORMATIONS
{

    uint8_t servo_motor1_degree;
    uint8_t servo_motor1_bottom_degree;
    uint8_t servo_motor1_top_degree;

    uint8_t servo_motor2_degree;
    uint8_t servo_motor2_bottom_degree;
    uint8_t servo_motor2_top_degree;

    uint32_t step_motor1_position;
    uint32_t step_motor1_max_step;

    uint32_t step_motor2_position;
    uint32_t step_motor2_max_step;



    operator CONTROL_DATA_FORMAT()
    {
        CONTROL_DATA_FORMAT control_data;

        control_data.servo_motor1_degree = servo_motor1_degree;
        control_data.servo_motor1_bottom_degree = servo_motor1_bottom_degree;
        control_data.servo_motor1_top_degree = servo_motor1_top_degree;

        control_data.servo_motor2_degree = servo_motor2_degree;
        control_data.servo_motor2_bottom_degree = servo_motor2_bottom_degree;
        control_data.servo_motor2_top_degree = servo_motor2_top_degree;

        control_data.step_motor1_step = step_motor1_position;
        control_data.step_motor2_step = step_motor2_position;

        return control_data;

    }

    MOTOR_INFORMATIONS operator =(CONTROL_DATA_FORMAT &ControlData)
    {
        servo_motor1_degree = ControlData.servo_motor1_degree;
        servo_motor1_bottom_degree = ControlData.servo_motor1_bottom_degree;
        servo_motor1_top_degree = ControlData.servo_motor1_top_degree;

        servo_motor2_degree = ControlData.servo_motor2_degree;
        servo_motor2_bottom_degree = ControlData.servo_motor2_bottom_degree;
        servo_motor2_top_degree = ControlData.servo_motor2_top_degree;

        step_motor1_position = ControlData.step_motor1_step;
        step_motor2_position = ControlData.step_motor2_step;

        return *this;
    }


};

struct REMOTEMACHINE_INFORMATIONS
{
    std::string stream_ip;

    int stream_port;
    int control_port;
};


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

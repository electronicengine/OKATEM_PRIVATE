#ifndef ENVIRONMENTINTERFACE_H
#define ENVIRONMENTINTERFACE_H

#include "lorawan.h"
#include "sfpmonitor.h"
#include "lasertracker.h"
#include "json.h"
#include "mainoperation.h"


class EnvironmentInterface : public MainOperation
{

public:
    EnvironmentInterface(MainOperation *Operation);

    void getEnvironment();
    void getJson();
    void saveBoardData(const INFORMATION_DATA_FORMAT &InformationData);
    void saveThread(const INFORMATION_DATA_FORMAT &InformationData);
    void saveMotorPositions(const MOTOR_INFORMATIONS &MotorInfo);

private:

    Json gmJson;
    LoraWan gmLora;

    LORA_INFO gmLoraData;
    LORA_INFO gmStmData;
    JSON_SENSOR_INFORMATIONS gmJsonInformationData;
    CONTROL_DATA_FORMAT gmControlData;
    INFORMATION_DATA_FORMAT gmInformationData;

};

#endif // ENVIRONMENTINTERFACE_H

#include "environmentinterface.h"
#include <thread>

EnvironmentInterface::EnvironmentInterface(MainOperation *Operation) : MainOperation(Operation)
{

    int ret;

    ret = gmJson.init();
    if(ret != SUCCESS)
        printAll("Json has been not initialize!");

//    ret = gmLora.init();
//    if(ret != SUCCESS)
//        printAll("Lora has been not initialize!");

    getJson();
}



void EnvironmentInterface::getJson()
{
    *gpMotorInformations = gmJson.loadMotorInfo();
    *gpRemoteMachineInfo = gmJson.loadStreamInfo();
}



void EnvironmentInterface::saveBoardData(const INFORMATION_DATA_FORMAT &InformationData)
{

    std::thread save(&EnvironmentInterface::saveThread, this, InformationData);
    save.detach();


}



void EnvironmentInterface::saveThread(const INFORMATION_DATA_FORMAT &InformationData)
{
    JSON_SENSOR_INFORMATIONS json_sensor_informations;

    json_sensor_informations.lora_environment_data = gmLora.getLoraData().environment_data;
    json_sensor_informations.lora_sfp_data = gmLora.getLoraData().sfp_data;

    json_sensor_informations.stm_environment_data = InformationData.environment_data;
    json_sensor_informations.sfp_data = InformationData.sfp_data;

    gmJson.saveBoardInfo(json_sensor_informations);
}



void EnvironmentInterface::saveMotorPositions(const MOTOR_INFORMATIONS &MotorInfo)
{
    *gpMotorInformations = MotorInfo;
    gmJson.saveMotorInfo(MotorInfo);
}







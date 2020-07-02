#include "mainoperation.h"
#include "environmentinterface.h"
#include "driverinterface.h"
#include "remotecontrolinterface.h"
#include "lasertracker.h"

MainOperation::MainOperation()
{

    gpInformationData = new INFORMATION_DATA_FORMAT;
    gpRemoteMachineInfo = new REMOTEMACHINE_INFORMATIONS;
    gpMotorInformations = new MOTOR_INFORMATIONS;

    gpEnvironmentInterface = new EnvironmentInterface(this);
    gpDriverInterface = new DriverInterface(this);
    gpRemoteControllerInterface = new RemoteControlInterface(this);
    gpTracker = new LaserTracker(this);

}

MainOperation::MainOperation(MainOperation *Operation)
{

    gpMotorInformations = Operation->gpMotorInformations;
    gpRemoteMachineInfo = Operation->gpRemoteMachineInfo;

    gpEnvironmentInterface = Operation->gpEnvironmentInterface;
    gpDriverInterface = Operation->gpDriverInterface;
    gpRemoteControllerInterface = Operation->gpRemoteControllerInterface;
    gpTracker = Operation->gpTracker;

}






int MainOperation::exec()
{
//    CONTROL_DATA_FORMAT control_data;

    while(1)
    {

//        udp_controller_socket.saveInformationData(gmControlData, stm_data ,sfp_data);

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

                printAll("Lora  Data: ", "\n", "Gps:  ", lora_stm_data.gps_string.substr(0,lora_stm_data.gps_string.find('*')),
                " - Temperature: ", (int)lora_stm_data.sensor_data.temperature,
                " - Altitude: ", (int)lora_stm_data.sensor_data.altitude,
                " - Pressure: ", (int)lora_stm_data.sensor_data.pressure,
                " - Compass: ", (int)lora_stm_data.sensor_data.compass_degree,
                " - Wheather: ", (int)lora_stm_data.sensor_data.wheather_condition,
                " - Sfp status: ", (lora_sfp_data.status == 1) ? "Connected" : "Disconnected");

            printAll("\n\n\n");

        sleep(1);
    }

    return 0;

}







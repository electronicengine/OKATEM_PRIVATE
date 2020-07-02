#ifndef MainOperation_H
#define MainOperation_H

#include "datatypes.h"
#include "udpsocket.h"

class EnvironmentInterface;
class DriverInterface;
class RemoteControlInterface;
class LaserTracker;

class MainOperation
{


public:
    MainOperation();
    MainOperation(MainOperation *Operation);

    int exec();

    void controlDataCallBack(const CONTROL_DATA_FORMAT &ControlData);
    void updateDataCallBack(const UPDATE_FILE_FORMAT &UpdateFile);
    void cameraSettingsDataCallBack(const CAMERA_SETTINGS_FORMAT &CameraSettings);


protected:

    CONTROL_DATA_FORMAT *gpControlData;
    INFORMATION_DATA_FORMAT *gpInformationData;
    MOTOR_INFORMATIONS  *gpMotorInformations;
    REMOTEMACHINE_INFORMATIONS *gpRemoteMachineInfo;

    RemoteControlInterface *gpRemoteControllerInterface;
    DriverInterface *gpDriverInterface;
    EnvironmentInterface *gpEnvironmentInterface;
    LaserTracker *gpTracker;


private:



};

#endif // MainOperation_H

#ifndef DRIVERINTERFACE_H
#define DRIVERINTERFACE_H

#include "lorawan.h"
#include "sfpmonitor.h"
#include "lasertracker.h"
#include "cameradriver.h"
#include "stmdriver.h"
#include "json.h"
#include "mainoperation.h"

class DriverInterface : public MainOperation
{
public:
    DriverInterface(MainOperation *Operation);
    void driveStmBoard(const CONTROL_DATA_FORMAT &ControlData);
    void updateStmBoard(const UPDATE_FILE_FORMAT &UpdateData);
    CAMERA_SETTINGS_FORMAT setCameraOptions(const CAMERA_SETTINGS_FORMAT &CameraSettings);

    void fillInformationData(INFORMATION_DATA_FORMAT);
    INFORMATION_DATA_FORMAT getInformationData();

private:

    CameraDriver gmCameraDriver;
    StmDriver gmStmDriver;
    SfpMonitor gmSfpDriver;


    int checkIfUdpCalibrationValues(const CONTROL_DATA_FORMAT &ControlData);

    CONTROL_DATA_FORMAT gmControlData;

};

#endif // DRIVERINTERFACE_H

#include "driverinterface.h"
#include "environmentinterface.h"

DriverInterface::DriverInterface(MainOperation *Operation) : MainOperation(Operation)
{
    int ret;

    ret = gmStmDriver.init();
    if(ret != SUCCESS)
        printAll("StmDriver has been not initialize!!!");

    ret = gmCameraDriver.init();
    if(ret != SUCCESS)
        printAll("CameraDriver has been not initialize!!!");


    ret = gmSfpDriver.init();
    if(ret != SUCCESS)
        printAll("Sfp Monitor has been not initialize!");



    gmStmDriver.setMotorCalibrationValues(*gpMotorInformations);
}

void DriverInterface::driveStmBoard(const CONTROL_DATA_FORMAT &ControlData)
{

    MOTOR_INFORMATIONS motor_informations;

    gmControlData = ControlData;

    motor_informations = ControlData;

    if(checkIfUdpCalibrationValues(ControlData) != SUCCESS)
    {
        gmStmDriver.setControlData(ControlData);
    }
    else
    {
        gmStmDriver.resetStm();
        gmStmDriver.setMotorCalibrationValues(motor_informations);
        gpEnvironmentInterface->saveMotorPositions(motor_informations);
    }
}



void DriverInterface::updateStmBoard(const UPDATE_FILE_FORMAT &UpdateData)
{

    gmStmDriver.setUpdateData(UpdateData);

}



CAMERA_SETTINGS_FORMAT DriverInterface::setCameraOptions(const CAMERA_SETTINGS_FORMAT &CameraSettings)
{

    CAMERA_SETTINGS_FORMAT camera_settings;

    if(CameraSettings.write_enable == 0)
    {
        std::cout << "camera settings request"<< std::endl;

        int ret = 0;

        camera_settings = gmCameraDriver.getCameraControls();

        camera_settings.write_enable = 0;

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

        if(ret == FAIL)
            printAll("Camera Setting Information can not be sent!");

        return camera_settings;

    }
    else if(CameraSettings.write_enable == 0xff)
    {
        camera_settings.write_enable = 0xff;

        gmCameraDriver.setCameraControls(CameraSettings);

        return camera_settings;
    }

}

INFORMATION_DATA_FORMAT DriverInterface::getInformationData()
{

    INFORMATION_DATA_FORMAT information_data;

    information_data.control_data = *gpMotorInformations;
    information_data.environment_data = gmStmDriver.getStmEnvironment();
    information_data.sfp_data = gmSfpDriver.getValues();

    gpEnvironmentInterface->saveBoardData(information_data);


    return information_data;
}



int DriverInterface::checkIfUdpCalibrationValues(const CONTROL_DATA_FORMAT &ControlData)
{
    if(ControlData.setting_enable == 0xff)
    {

        printAll("Calibration Values are setting...");

        return SUCCESS;

    }
    else
        return FAIL;
}




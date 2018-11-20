#ifndef LCDHMI_H
#define LCDHMI_H

#include "serialcom.h"
#include "globals.h"
#include "queue.h"

#define INTRO_PAGE_ID           0x00
#define MAIN_PAGE_ID            0x01
#define MANUAL_PAGE_ID          0x02
#define TEST_PAGE_ID            0x03
#define INFO_PAGE_ID            0x04
#define SENSORS_PAGE_ID         0x05
#define AUTO_PAGE_ID            0x06
#define CAMERA_PAGE_ID          0x07

#define HEADER                  0xff
#define FOOTER                  0xfd

#define AUTOMODE_START          0x02
#define AUTOMODE_PAUSE          0x04
#define AUTOMODE_STOP           0x03


#define CALLBACKTOKEN           0x08
#define PAGE_CHANGED            0x09
#define BUTTON_PRESSED          0x10
#define BUTTON_UNPRESSED        0x11

#define UP_BUTTON_ID            0x04
#define DOWN_BUTTON_ID          0x03
#define LEFT_BUTTON_ID          0x02
#define RIGHT_BUTTON_ID         0x01


#define CAMERA1_UP_BUTTON_ID    0x02
#define CAMERA1_DOWN_BUTTON_ID  0x01
#define CAMERA2_UP_BUTTON_ID    0x07
#define CAMERA2_DOWN_BUTTON_ID  0x06

#define CALIBRATE_BUTTON_ID     0x09



class LcdHMI
{

public:

    LcdHMI();

    CONTROL_DATA_FORMAT getHCMControlData();
    Status setInitialMotorPositions(CONTROL_DATA_FORMAT &SavedData);
    Status setHCMData(SFP_DATA_FORMAT& SfpData, ENVIRONMENT_DATA_FORMAT& EnvironmentData);



private:

    bool gmDataComing = false;
    bool gmAutoModeEnable = false;

    uint32_t servo_motor1_angle = 50;
    uint32_t servo_motor2_angle = 50;

    SerialCom *gmSerial;

    std::mutex gmMutex;
    CONTROL_DATA_FORMAT gmControlData;
    ENVIRONMENT_DATA_FORMAT gmStmEnvironmentData;
    SFP_DATA_FORMAT gmSfpData;

    unsigned char gmCurrentPage;

    void callSensorPage(std::vector<unsigned char>& Data);
    void callManualPage(std::vector<unsigned char>& Data);
    void callAutoPage(std::vector<unsigned char>& Data);
    void callCameraPage(std::vector<unsigned char>& Data);

    void initHCM();
    void listenHMI();
    void autoMode();
    Status sendEnvironmentInfo();


};

#endif // LCDHMI_H
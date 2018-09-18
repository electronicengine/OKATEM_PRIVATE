#ifndef LCDHMI_H
#define LCDHMI_H

#include "serialcom.h"
#include "globals.h"

#define INTRO_PAGE_ID       0x00
#define MAIN_PAGE_ID        0x01
#define MANUAL_PAGE_ID      0x02
#define TEST_PAGE_ID        0x03
#define INFO_PAGE_ID        0x04
#define SENSORS_PAGE_ID     0x05
#define AUTO_PAGE_ID        0x06
#define CAMERA_PAGE_ID      0x07

#define HEADER              0xff
#define FOOTER              0xfd

#define PAGE_CHANGED        0x09
#define BUTTON_PRESSED      0x10
#define BUTTON_UNPRESSED    0x11

#define UP_BUTTON_ID        0x04
#define DOWN_BUTTON_ID      0x03
#define LEFT_BUTTON_ID      0x02
#define RIGHT_BUTTON_ID     0x01




class LcdHMI
{

public:

    LcdHMI();

    CONTROL_DATA_FORMAT getHCMControlData();
    Status setHCMData(SFP_DATA_FORMAT& SfpData, ENVIRONMENT_DATA_FORMAT& EnvironmentData);



private:

    bool gmDataComing = false;

    std::mutex gmMutex;
    CONTROL_DATA_FORMAT gmControlData;
    ENVIRONMENT_DATA_FORMAT gmStmEnvironmentData;
    SFP_DATA_FORMAT gmSfpData;

    unsigned char gmCurrentPage;

    void writeControlData(std::vector<unsigned char>& Data);
    void initHCM();
    void listenHMI();


};

#endif // LCDHMI_H

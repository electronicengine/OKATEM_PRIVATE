#ifndef SpiDriver_H
#define SpiDriver_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <cmath>

#include "globals.h"
#include "spicom.h"
#include "queue.h"
#include "json.h"

#define CONTROLLER_PORT 24000
#define RESET_TIMEOUT 40
#define FORWARD 1
#define BACKWARD 2
#define STOP 0


class StmDriver
{
public:



    StmDriver();
    ~StmDriver();

    int init();
    void resetStm();

    Status isReady();

    Status driveMotorLeft();
    Status driveMotorRight();
    Status driveMotorDown();
    Status driveMotorUp();

    Status setControlData(const CONTROL_DATA_FORMAT& Data);
    Status setUpdateData(const UPDATE_FILE_FORMAT& Data);

    void setMotorCalibrationValues(const MOTOR_INFORMATIONS &MotorInformations);


    ENVIRONMENT_DATA_FORMAT getStmEnvironment();



private:

    SPI_TRANSFER_FORMAT gmSpiTxData;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentData;
    CONTROL_DATA_FORMAT gmControlData;
    Queue<UPDATE_FILE_FORMAT> gmUpdateFile;

    volatile bool gmUpdateAvalilable = false;
    volatile bool gmIsReceived = false;
    volatile bool gmIsTransmitted = true;
    volatile bool gmResetStm = false;

    MOTOR_INFORMATIONS gmCalibratedMotorValues;

    SpiCom gmSpi;
    std::mutex gmMutex;



    int checkInitilizationNeeded(ENVIRONMENT_DATA_FORMAT &EnvironmentData);
    void communicationThread();
    void processUpdateData(const SPI_TRANSFER_FORMAT& UpdateData);
    void putEnvironmentDataIntoBuffer(const SPI_TRANSFER_FORMAT& SpiData);
    Status checkValidEnvironmentData(ENVIRONMENT_DATA_FORMAT& Data);


};

#endif // StmDriver_H

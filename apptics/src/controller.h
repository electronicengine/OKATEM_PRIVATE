#ifndef Controller_H
#define Controller_H

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

#define FORWARD 1
#define BACKWARD 2
#define STOP 0


class Controller
{
public:



    Controller();
    ~Controller();

    int init();
    void resetStm();

    Status isReady();

    Status zoomInCamera();
    Status zoomOutCamera();

    Status driveMotorLeft();
    Status driveMotorRight();
    Status driveMotorDown();
    Status driveMotorUp();

    Status setControlData(CONTROL_DATA_FORMAT& Data);
    Status setUpdateData(UPDATE_FILE_FORMAT& Data);

    void setMotorCalibrationValues(const MOTOR_INFORMATIONS &MotorInformations);


    ENVIRONMENT_DATA_FORMAT getStmEnvironment();



private:

    SPI_TRANSFER_FORMAT gmSpiTxData;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentData;
    CONTROL_DATA_FORMAT gmControlData;
    UPDATE_FILE_FORMAT gmUpdateFile;


    volatile bool gmIsReceived = false;
    volatile bool gmIsTransmitted = true;

    MOTOR_INFORMATIONS gmCalibratedMotorValues;

    volatile uint32_t gmDesiredPackageSequence = 1;
    volatile uint32_t gmCurrentPackageSequence = 1;

    SpiCom gmSpi;
    std::mutex gmMutex;



    int checkInitilizationNeeded(ENVIRONMENT_DATA_FORMAT &EnvironmentData);
    void communicationThread();
    Status checkIfUpdateData(const SPI_TRANSFER_FORMAT& SpiData);
    Status checkIfEnvironmentData(const SPI_TRANSFER_FORMAT& SpiData);
    Status checkValidEnvironmentData(ENVIRONMENT_DATA_FORMAT& Data);


};

#endif // Controller_H

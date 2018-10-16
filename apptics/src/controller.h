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




class Controller
{
public:



    Controller();
    ~Controller();

    Status isReady();

    Status zoomInCamera();
    Status zoomOutCamera();

    Status driveMotorLeft();
    Status driveMotorRight();
    Status driveMotorDown();
    Status driveMotorUp();

    Status setControlData(CONTROL_DATA_FORMAT& Data);
    Status setUpdateData(UPDATE_FILE_FORMAT& Data);

    ENVIRONMENT_DATA_FORMAT getStmEnvironment();



private:

    SPI_TRANSFER_FORMAT gmSpiTxData;
    SPI_TRANSFER_FORMAT gmSpiRxData;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentData;
    CONTROL_DATA_FORMAT gmControlData;

    volatile bool gmIsReceived = false;
    volatile bool gmIsTransmitted = true;


    uint32_t gmDesiredPackageSequence = 1;
    uint32_t gmCurrentPackageSequence = 1;

    SpiCom gmSpi;

    std::mutex gmMutex;

    UPDATE_FILE_FORMAT gmBackupUpdateFile;
    UPDATE_FILE_FORMAT gmUpdateFile;

    void communicationThread();
    Status checkIfUpdateData(const SPI_TRANSFER_FORMAT& SpiData);
    Status checkIfEnvironmentData(const SPI_TRANSFER_FORMAT& SpiData);


};

#endif // Controller_H

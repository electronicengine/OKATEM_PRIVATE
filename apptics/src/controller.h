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


#define FORWARD 1
#define BACKWARD 2



class Controller
{
public:

    enum class Controller_Status
    {
        time_out,
        error,
        ok

    }Status;

    Controller();
    ~Controller();

    Controller_Status isReady();

    Controller_Status zoomInCamera();
    Controller_Status zoomOutCamera();

    Controller_Status driveMotorLeft();
    Controller_Status driveMotorRight();
    Controller_Status driveMotorDown();
    Controller_Status driveMotorUp();

    Controller_Status setControlData(CONTROL_DATA_FORMAT& Data);
    Controller_Status setUpdateData(UPDATE_FILE_FORMAT& Data);

    ENVIRONMENT_DATA_FORMAT getStmEnvironment();



private:

    SPI_TRANSFER_FORMAT gmSpiTxData;
    SPI_TRANSFER_FORMAT gmSpiRxData;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentData;
    CONTROL_DATA_FORMAT gmControlData;

    volatile bool gmIsReceived = false;
    volatile bool gmIsTransmitted = false;
    volatile bool gmCorruptedPackage = false;

    uint32_t gmDesiredPackageSequence = 1;
    uint32_t gmCurrentPackageSequence = 1;

    SpiCom gmSpi;

    std::mutex gmMutex;

    UPDATE_FILE_FORMAT gmBackupUpdateFile;
    UPDATE_FILE_FORMAT gmUpdateFile;

    void communicationThread();


};

#endif // Controller_H

#include "controller.h"
#include "globals.h"

Controller::Controller()
{

    std::thread communication(&Controller::communicationThread, this);
    communication.detach();
}

Controller::~Controller()
{

}

Controller::Bpi_Status Controller::setControlData(const SPI_TX_FORMAT &Data)
{
    gmMutex.lock();
    gmBPIControlData = Data;
    gmMutex.unlock();
}

SPI_RX_FORMAT Controller::getStmEnvironment()
{
    SPI_RX_FORMAT Data;

    gmMutex.lock();
    Data = gmStmEnvironmentData;
    gmMutex.unlock();

    return Data;
}

void Controller::communicationThread()
{

    unsigned char transmitted_data[SPI_TRANSFER_SIZE];


    while(true)
    {

        gmMutex.lock();

//        transmitted_data = (unsigned char *)gmBPIControlData;
        gmSpi.spiTransmiteReceive((unsigned char *)transmitted_data, SPI_TRANSFER_SIZE);
        gmStmEnvironmentData = (unsigned char *)transmitted_data;


        gmMutex.unlock();

        usleep(100000);
    }

}

#include "bananapi.h"
#include "globals.h"

BananaPi::BananaPi()
{

    std::thread communication(&BananaPi::communicationThread, this);
    communication.detach();
}

BananaPi::~BananaPi()
{

}

BananaPi::Bpi_Status BananaPi::setControlData(const SPI_TX_FORMAT &Data)
{
    gmMutex.lock();
    gmBPIControlData = Data;
    gmMutex.unlock();
}

SPI_RX_FORMAT BananaPi::getStmEnvironment()
{
    SPI_RX_FORMAT Data;

    gmMutex.lock();
    Data = gmStmEnvironmentData;
    gmMutex.unlock();

    return Data;
}

void BananaPi::communicationThread()
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

#include "bananapi.h"
#include "globals.h"

BananaPi::BananaPi()
{
//    gmBPIControlData = new SPI_TX_FORMAT;
//    gmStmEnvironmentData = new SPI_RX_FORMAT;

    std::thread communication(&BananaPi::communicationThread, this);
    communication.detach();
}

BananaPi::~BananaPi()
{
//    delete gmBPIControlData;
//    delete gmStmEnvironmentData;
}

BananaPi::Bpi_Status BananaPi::setControlData(const SPI_TX_FORMAT &Data)
{
    gmMutex.lock();
    gmBPIControlData = Data;
    gmMutex.unlock();
}

BananaPi::Bpi_Status BananaPi::getStmEnvironment(SPI_RX_FORMAT Data)
{
    gmMutex.lock();
    gmStmEnvironmentData = Data;
    gmMutex.unlock();
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

//        printAll("Gps Data:  ", std::string((char *)gmStmEnvironmentData->gps_data));
//        printAll("Temperature: ", (int)gmStmEnvironmentData->temperature);
//        printAll("Altitude: ", (int)gmStmEnvironmentData->altitude);
//        printAll("Pressure: ", (int)gmStmEnvironmentData->pressure);
//        printAll("Wheather: ", (int)gmStmEnvironmentData->wheather_condition);

        gmMutex.unlock();

        usleep(100000);
    }

}

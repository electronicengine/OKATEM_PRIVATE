#include "sfpmonitor.h"
#include "globals.h"




SfpMonitor::SfpMonitor()
{
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", ADAPTER_NUMBER);
    gmFileDescriptor = open(filename, O_RDWR);
    if (gmFileDescriptor < 0) {
        // TODO: Handle this
        printAll("I2C ports could not open");

    }

    if (ioctl(gmFileDescriptor, I2C_SLAVE, SFP_I2C_DIAG_ADDRESS) < 0) {
        // TODO: Handle this
        printAll("I2C address could not write");
    }


    std::thread monitoring(&SfpMonitor::runSfpMonitor, this);
    monitoring.detach();

}

SfpMonitor::~SfpMonitor()
{
    close(gmFileDescriptor);
}

SFP_DATA SfpMonitor::getValues()
{
    SFP_DATA data;

    gmMutex.lock();
    data = gmSfpData;
    gmMutex.unlock();

    return data;


}


float SfpMonitor::getTemperature()
{

    float temperature;

    gmMutex.lock();
    temperature = gmSfpData.temperature;
    gmMutex.unlock();

    return temperature;

}

float SfpMonitor::getVcc()
{

    float vcc;

    gmMutex.lock();
    vcc = gmSfpData.vcc;
    gmMutex.unlock();

    return vcc;
}

float SfpMonitor::getTxBias()
{

    float tx_bias;

    gmMutex.lock();
    tx_bias = gmSfpData.tx_bias;
    gmMutex.unlock();

    return tx_bias;


}

float SfpMonitor::getTxPower()
{

    float tx_power;

    gmMutex.lock();
    tx_power = gmSfpData.tx_power;
    gmMutex.unlock();

    return tx_power;
}

float SfpMonitor::getRxPower()
{

    float rx_power;

    gmMutex.lock();
    rx_power = gmSfpData.rx_power;
    gmMutex.unlock();

    return rx_power;
}

bool SfpMonitor::getSfpConnectionState()
{

    bool status;

    gmMutex.lock();
    status = gmSfpData.status;
    gmMutex.unlock();

    return status;
}



int SfpMonitor::readValues()
{
    // TODO: Check type of the value, default is current value
    if (!this->readData())
        return -1;

    gmSfpData.temperature = convertNumber((uint8_t *)&gmBuffer[96], 256, true);
    gmSfpData.vcc = convertNumber((uint8_t *)&gmBuffer[98], 10000, false);
    gmSfpData.tx_bias = convertNumber((uint8_t *)&gmBuffer[100], 500, false);
    gmSfpData.tx_power = convertNumber((uint8_t *)&gmBuffer[102], 10000, false);
    gmSfpData.rx_power = convertNumber((uint8_t *)&gmBuffer[104], 10000, false);

    if(gmSfpData.rx_power * 1000 > 2)
        gmSfpData.status = true;
    else
        gmSfpData.status = false;

    return 0;
}

void SfpMonitor::runSfpMonitor()
{
    int ret;

    while(1)
    {

        gmMutex.lock();
        ret = readValues();
        gmMutex.unlock();

        if(ret < 0)
            printAll("SfpMonitor getValues is failed");

        usleep(10000);

    }

}

int SfpMonitor::readData()
{
    char temp = 0x00;

    if (write(gmFileDescriptor, &temp, 1) != 1) {
        return 0;
    }

    memset(gmBuffer, '0', 256);
    for (int i = 0; i <= 255; i++){
        if (read(gmFileDescriptor, gmBuffer + i, 1) != 1) {
            return i;
        }
    }

    return 255;
}

inline float SfpMonitor::convertNumber(uint8_t *Data, uint16_t Divisor, bool IsSigned)
{
    if (IsSigned) {
        return ((int16_t) ((Data[0] << 8) + Data[1])) / (float) Divisor;
    } else {
        return ((uint16_t) ((Data[0] << 8) + Data[1])) / (float) Divisor;
    }
}

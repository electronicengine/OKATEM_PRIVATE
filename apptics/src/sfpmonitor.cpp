#include "sfpmonitor.h"



extern std::map<std::string, bool> CheckList;


SfpMonitor::SfpMonitor()
{


}

SfpMonitor::~SfpMonitor()
{
    close(gmFileDescriptor);
}

int SfpMonitor::init()
{
    int ret;
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", ADAPTER_NUMBER);
    gmFileDescriptor = open(filename, O_RDWR);

    if (gmFileDescriptor < 0) {
        // TODO: Handle this
        printAll("I2C ports could not open");
        return FAIL;

    }

    if (ioctl(gmFileDescriptor, I2C_SLAVE, SFP_I2C_DIAG_ADDRESS) < 0) {
        // TODO: Handle this
        printAll("I2C address could not write");
        return FAIL;
    }

    ret = gmRoutingTable.init();
    if(ret != SUCCESS)
    {
       printAll("Routeing Tables couldn't init!!");
       return FAIL;
    }


    std::thread monitoring(&SfpMonitor::runSfpMonitor, this);
    monitoring.detach();

    return SUCCESS;
}

SFP_DATA_FORMAT SfpMonitor::getValues()
{
    SFP_DATA_FORMAT data;

    gmMutex.lock();
    data = gmSfpData;
    gmMutex.unlock();

    return data;


}


float SfpMonitor::getTemperature()
{

    float temperature;

    gmMutex.lock();
    temperature = gmSfpData.sfp_temperature;
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



SFP_DATA_FORMAT SfpMonitor::readValues()
{
    SFP_DATA_FORMAT sfp_data;
    // TODO: Check type of the value, default is current value
    if (!this->readData())
    {
//        CheckList["SfpMonitor"] = false;
        printAll("can not read sfp values !!!");
    }

    sfp_data.sfp_temperature = convertNumber((uint8_t *)&gmBuffer[96], 256, true);
    sfp_data.vcc = convertNumber((uint8_t *)&gmBuffer[98], 10000, false);
    sfp_data.tx_bias = convertNumber((uint8_t *)&gmBuffer[100], 500, false);
    sfp_data.tx_power = convertNumber((uint8_t *)&gmBuffer[102], 10000, false);
    sfp_data.rx_power = convertNumber((uint8_t *)&gmBuffer[104], 10000, false);

    if(sfp_data.rx_power * 1000 > 2)
        sfp_data.status = SFP_CONNECTED;
    else
        sfp_data.status = SFP_DISCONNECTED;

    return sfp_data;
}

void SfpMonitor::runSfpMonitor()
{
    bool sfp_available = false;
    bool wifi_available = false;

    int ret;
    SFP_DATA_FORMAT sfp_data;

    printAll("SfpMonitor is starting...");

    while(1)
    {
        sfp_data = readValues();

        if(sfp_data.status == SFP_CONNECTED && sfp_available == false)
        {
            wifi_available = false;
            sfp_available = true;
            gmRoutingTable.switchSfp();
        }
        else if(sfp_data.status == SFP_DISCONNECTED && wifi_available == false)
        {
            sfp_available = false;
            wifi_available = true;
            gmRoutingTable.switchRF();
        }

        gmMutex.lock();
        gmSfpData = sfp_data;
        gmMutex.unlock();

        usleep(100000);

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

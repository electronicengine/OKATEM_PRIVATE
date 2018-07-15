#ifndef SFPMONITOR_H
#define SFPMONITOR_H


#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <thread>
#include <mutex>

#define ADAPTER_NUMBER (int)1

#define SFP_I2C_INFO_ADDRESS 0x50
#define SFP_I2C_DIAG_ADDRESS 0x51

#define SFP_DIAG_VALUE_OFFSET 96
#define SFP_DIAG_VALUE_STRIDE 26


struct SFP_DATA
{
    int type;
    float temperature;
    float vcc;
    float tx_bias;
    float tx_power;
    float rx_power;
    bool status;

};



class SfpMonitor
{
public:


    SfpMonitor();
    ~SfpMonitor();


    SFP_DATA getValues();
    float getTemperature();
    float getVcc();
    float getTxBias();
    float getTxPower();
    float getRxPower();
    bool  getSfpConnectionState();

private:

    SFP_DATA gmSfpData;
    int gmFileDescriptor;
    char gmBuffer[256];
    std::mutex gmMutex;

    void runSfpMonitor();
    int readData();
    int readValues();

    inline float convertNumber(uint8_t *Data, uint16_t Divisor, bool IsSigned);
};

#endif // SFPMONITOR_H

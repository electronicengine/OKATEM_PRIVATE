#ifndef LORAWAN_H
#define LORAWAN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <mutex>

#include "serialcom.h"
#include "stmdriver.h"
#include "sfpmonitor.h"


#define TRANSMISSION_SIZE 64
#define TRANSMISSION_TIMEOUT 10

struct LORA_INFO
{
    SFP_DATA_FORMAT sfp_data;
    ENVIRONMENT_DATA_FORMAT environment_data;
};


class LoraWan
{

public:

    LoraWan();
    LoraWan(std::string Power);
    LoraWan(std::string Power, std::string Freqency);

    Status scanArea();
    void sendBeacon();

    int init();
    void setLoraData(const LORA_INFO& LoraData);
    LORA_INFO getLoraData();
    void listen();

private:


    time_t gmLastBeacon = 0;
    time_t gmNow = 0;

    SFP_DATA_FORMAT gmLoraSfp;
    ENVIRONMENT_DATA_FORMAT gmLoraStm;

    SFP_DATA_FORMAT gmRecievedLoraSfp;
    ENVIRONMENT_DATA_FORMAT gmRecievedLoraStm;

    std::string gmBaundRate;
    std::string gmFrequency;

    int gmPower;
    int gmTimeout;

    SerialCom gmSerial;

    std::mutex gmMutex;

    int sendCommand(std::string Command);

    bool gmSerialPortInit = false;



    void callBack(std::string& CommingData);
    void collectData(std::string& Data);
    void listenChannel();
    void resetChannel();
    std::string prepareData();












};

#endif // LORAWAN_H

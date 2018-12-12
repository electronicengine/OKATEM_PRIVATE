#ifndef LORAWAN_H
#define LORAWAN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <mutex>

#include "serialcom.h"
#include "controller.h"
#include "sfpmonitor.h"


#define TRANSMISSION_SIZE 64
#define TRANSMISSION_TIMEOUT 10

struct Lora_Environment_Info
{

    GPS_DATA gps_data;


};


class LoraWan
{

public:

    LoraWan();
    LoraWan(std::string Power);
    LoraWan(std::string Power, std::string Freqency);

    Status scanArea();
    Status sendBeacon();

    int init();
    void setLoraData(const SFP_DATA_FORMAT& SfpData, const ENVIRONMENT_DATA_FORMAT& StmData);
    void getLoraData(SFP_DATA_FORMAT& SfpData, ENVIRONMENT_DATA_FORMAT& StmData);
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

#ifndef LORAWAN_H
#define LORAWAN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "serialcom.h"
#include "bananapi.h"
#include "sfpmonitor.h"
#include <time.h>
#include <random>
#include <mutex>


#define TRANSMISSION_SIZE 64
#define TRANSMISSION_TIMEOUT 10

struct Lora_Environment_Info
{

    GPS_DATA gps_data;


};


class LoraWan
{

public:

    enum class Lora_Status{
        init_error,
        send_error,
        receive_error
    };


    LoraWan();
    LoraWan(std::string Power);
    LoraWan(std::string Power, std::string Freqency);

    Lora_Status scanArea();
    Lora_Status sendBeacon();
    Lora_Status init();

    void setLoraData(SFP_DATA& SfpData, SPI_RX_FORMAT& StmData);
    void listen();

private:


    time_t gmLastBeacon = 0;
    time_t gmNow = 0;

    SFP_DATA gmLoraSfp;
    SPI_RX_FORMAT gmLoraStm;

    std::string gmBaundRate;
    std::string gmFrequency;

    int gmPower;
    int gmTimeout;

    SerialCom gmSerial;

    std::mutex gmMutex;

    void callBack(std::string& CommingData);
    void collectData(std::string& Data);
    void listenChannel();
    void resetChannel();












};

#endif // LORAWAN_H

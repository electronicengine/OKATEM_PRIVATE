#ifndef LORAWAN_H
#define LORAWAN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "serialcom.h"
#include "bananapi.h"

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


private:

    std::string gmBaundRate;
    std::string gmFrequency;
    int gmPower;
    int gmTimeout;
    SerialCom gmSerial;

    Lora_Status init();



    Lora_Status sendBeacon();
    Lora_Status listenChannel();









};

#endif // LORAWAN_H

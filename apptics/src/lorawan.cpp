#include "lorawan.h"



LoraWan::Lora_Status LoraWan::init()
{

    std::vector<unsigned char> lora_return;
    int return_size;
    std::string answer;

    do
    {
        gmSerial.writeData("radio set pwr ", 14, "\r\n");
        gmSerial.readData(lora_return, return_size = 0, 100);

        answer = std::string(lora_return.begin(), lora_return.end());

    }while(!strcmp("ok", answer.c_str()));

        printAll("Lora radio set pwr 14 : ", answer);
        lora_return.clear();

    gmSerial.writeData("mac pause\r\n");
    gmSerial.readData(lora_return, return_size = 0, 100);

    printAll("Lora mac pause :", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set wdt ", 0, "\r\n" );
        gmSerial.readData(lora_return, return_size = 0, 100);

        answer = std::string(lora_return.begin(), lora_return.end());

    }while(!strcmp("ok", answer.c_str()));

    printAll("Lora radio set wdt 0: ", answer);
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set freq ", gmFrequency, "\r\n" );
        gmSerial.readData(lora_return, return_size = 0, 100);

        answer = std::string(lora_return.begin(), lora_return.end());
    }while(!strcmp("ok", answer.c_str()));

    printAll("Lora radio set freq ", gmFrequency, " : ", answer);
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set mod fsk\r\n" );
        gmSerial.readData(lora_return, return_size = 0, 100);

        answer = std::string(lora_return.begin(), lora_return.end());
    }while(!strcmp("ok", answer.c_str()));

    printAll("Lora radio set mod fsk ", answer.c_str());
    lora_return.clear();

}



LoraWan::Lora_Status LoraWan::listenChannel()
{
    do{
        gmSerial.writeData("radio rx 0\r\n");
        gmSerial.readData(lora_return);

    }while(!strcmp);
}



LoraWan::LoraWan() : gmBaundRate("B57600"), gmFrequency("433100000")
{
    init();

}

LoraWan::LoraWan(std::string BaundRate) : gmBaundRate(BaundRate), gmFrequency("433100000")
{
    init();
}

LoraWan::LoraWan(std::string BaundRate, std::string Freqency) : gmBaundRate(BaundRate), gmFrequency(Freqency)
{
    init();
}


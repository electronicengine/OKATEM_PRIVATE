#include "lorawan.h"

LoraWan::Lora_Status LoraWan::init()
{
    std::vector<unsigned char> lora_return;
    int return_size;




        gmSerial.writeData("sys reset\r\n");
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

//        printAll(std::string(lora_return.begin(), lora_return.end()));
        lora_return.clear();
        usleep(1);


    do
    {
        gmSerial.writeData("radio set pwr ", 14, "\r\n");
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(1);

    }while( std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

//    printAll("Lora radio set pwr 14 : ", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();

    gmSerial.writeData("mac pause\r\n");
    gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

//    printAll("Lora mac pause :", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set wdt ", 0, "\r\n" );
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(TRANSMISSION_TIMEOUT);
    }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

//    printAll("Lora radio set wdt 0: ", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set freq ", gmFrequency, "\r\n" );
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(TRANSMISSION_TIMEOUT);

    }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

//    printAll("Lora radio set freq ", gmFrequency, " : ", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();

    do
    {

        gmSerial.writeData("radio set mod fsk\r\n" );
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(TRANSMISSION_TIMEOUT);
    }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

//    printAll("Lora radio set mod fsk ", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();


    sleep(std::rand() % 10);
    
}



LoraWan::Lora_Status LoraWan::sendBeacon()
{

    std::string Data =prepareData();


    int return_size;
    int size = Data.length();
    int sequence = size / TRANSMISSION_SIZE;

    std::string partial_data;
    std::string partial_header;
    std::vector<unsigned char> lora_return;

    if(size % TRANSMISSION_SIZE)
        sequence ++;


//    std::cout << "Size: " << size << std::endl;
//    std::cout << "sequence " << sequence << std::endl;


    for(int i=0; i<sequence; i++)
    {

        partial_data = "radio tx ";
        partial_header = " |" + std::to_string(i + 1) + "/" + std::to_string(sequence) + "| ";
        partial_header = convertToHex(partial_header);

        partial_data +=partial_header;

        if((i == sequence - 1) && (size % TRANSMISSION_SIZE))
            partial_data += Data.substr(i*TRANSMISSION_SIZE, (size - (i*TRANSMISSION_SIZE)));
        else
            partial_data += Data.substr(i*TRANSMISSION_SIZE, TRANSMISSION_SIZE);

        partial_data += "\r\n";



            do{

//                printAll(partial_data);

                gmSerial.writeData(partial_data);

                lora_return.clear();
                gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

//                std::cout << "tx: " << std::string(lora_return.begin(), lora_return.end()) << std::endl;

            }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\nradio_tx_ok\r\n");


        usleep(100000);

    }
}



void LoraWan::listenChannel()
{

    SerialCom::Serial_Status status;

    std::vector<unsigned char> lora_return;
    int return_size;
    std::string incoming_data;

    bool timeout = 0;

    while(1)
    {
        do
        {

            do
            {

                lora_return.clear();
                gmSerial.writeData("radio rx 0\r\n");
                status = gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

//              printAll(std::string(lora_return.begin(), lora_return.end()));
//              std::cout << "rx : " << std::string(lora_return.begin(), lora_return.end()) << std::endl;

            }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n" &&
                   std::string(lora_return.begin(), lora_return.end()) != "busy\r\n");
            lora_return.clear();

            status = gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);


            if(status == SerialCom::Serial_Status::time_out)
            {
                timeout = 1;
                break;
            }

        }while(std::string(lora_return.begin(), lora_return.end()) == "radio_err\r\n");

        if(timeout == 1)
            break;

        try
        {
            incoming_data = std::string(lora_return.begin(), lora_return.end()).substr(10, lora_return.size());
            incoming_data = convertHexToAscii(incoming_data);

            collectData(incoming_data);
        }
        catch( std::exception& exception )
        {
            printAll(exception.what());
            break;
        }

    }

    resetChannel();
//    printAll("\nLora Timeout\n");

}



void LoraWan::resetChannel()
{
    std::string beacon = "hello";

    init();

    sendBeacon();

    listen();

}

std::string LoraWan::prepareData()
{

    std::string Data;
    int gps_char_pos;

    gmMutex.lock();

    Data = std::string(gmLoraStm.gps_string);
    gps_char_pos = Data.find_first_of("*");
    Data = Data.substr(0, gps_char_pos);

    Data += " - Sensor Temp:" + std::to_string(gmLoraStm.sensor_data.temperature);
    Data += " - Sensor altitude: " + std::to_string(gmLoraStm.sensor_data.altitude);
    Data += " - Sensor pressure: " + std::to_string(gmLoraStm.sensor_data.pressure);
    Data += " - Sensor wheather: " + std::to_string(gmLoraStm.sensor_data.wheather_condition);
    Data += " - Sensor compass: " + std::to_string(gmLoraStm.sensor_data.compass_degree);
    Data += " - Sfp Status: " + std::to_string(gmLoraSfp.status);
    Data += " - end";



    gmMutex.unlock();


    Data = convertToHex(Data);

    return Data;

}



void LoraWan::collectData(std::string &Data)
{


    static std::string total_string;
    int seperator_pos;

    int sequence_num;
    int total_sequence;

    std::string substring;

    std::istringstream stream(Data);

    std::getline(stream, substring, '/');

    seperator_pos = substring.find_first_of('|');

    substring = substring.substr(seperator_pos + 1, substring.length());
    sequence_num = std::stoi(substring);

    std::getline(stream, substring, '|');
    total_sequence = std::stoi(substring);

    std::getline(stream, substring, '|');
    substring = substring.substr(1, substring.length());
    total_string += substring;

    if(total_sequence == sequence_num)
    {
        callBack(total_string);
        total_string.clear();
    }

}

void LoraWan::listen()
{

    std::thread lora(&LoraWan::listenChannel, this);
    lora.detach();

}



void LoraWan::setLoraData(const SFP_DATA &SfpData, const SPI_RX_FORMAT &StmData)
{

    gmMutex.lock();

    gmLoraSfp = SfpData;
    gmLoraStm = StmData;

    gmMutex.unlock();

}

void LoraWan::getLoraData(SFP_DATA &SfpData, SPI_RX_FORMAT &StmData)
{

    gmMutex.lock();

    SfpData = gmRecievedLoraSfp;
    StmData = gmRecievedLoraStm;

    gmMutex.unlock();

}



void LoraWan::callBack(std::string& CommingData)
{


    int i = 0;
    int pos;

    std::string delimiter = "-";
    std::string token[20];


    while ((pos = CommingData.find(delimiter)) != std::string::npos)
    {

        token[i] = CommingData.substr(0, pos);
        CommingData.erase(0, pos + delimiter.length());
        i++;
    }


    gmMutex.lock();

    gmRecievedLoraStm.gps_string = token[0];
    gmRecievedLoraStm.sensor_data.temperature = (uint32_t) std::stoi(token[1].substr(token[1].find(":") + 1, token[1].length()));
    gmRecievedLoraStm.sensor_data.altitude = (uint32_t) std::stoi(token[2].substr( token[2].find(":") + 1, token[2].length()));
    gmRecievedLoraStm.sensor_data.pressure = (uint32_t) std::stoi(token[3].substr( token[3].find(":") + 1, token[3].length()));
    gmRecievedLoraStm.sensor_data.wheather_condition = (uint8_t) std::stoi(token[4].substr( token[4].find(":") + 1, token[4].length()));
    gmRecievedLoraStm.sensor_data.compass_degree = (uint32_t) std::stoi(token[5].substr(token[5].find(":") + 1, token[5].length()));
    gmRecievedLoraSfp.status = (int)std::stoi(token[6].substr( token[6].find(":") + 1, token[6].length()));



//    printAll("Lora Data: ");
//    printAll("temperature: ", (int)gmRecievedLoraStm.sensor_data.temperature,
//    " - altitude: ", (int)gmRecievedLoraStm.sensor_data.altitude,
//    " - pressure: ", (int)gmRecievedLoraStm.sensor_data.pressure,
//    " - wheather_condition: ", (int)gmRecievedLoraStm.sensor_data.wheather_condition,
//    " - compass_degree: ", (int)gmRecievedLoraStm.sensor_data.compass_degree,
//    " - Sfp status: ", gmRecievedLoraSfp.status);

//    printAll("\n\n\n");


    gmMutex.unlock();



    usleep(1000000);

    sendBeacon();


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


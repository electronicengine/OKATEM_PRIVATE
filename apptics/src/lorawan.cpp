#include "lorawan.h"
#include "globals.h"


extern std::map<const std::string, bool> CheckList;



Status LoraWan::init()
{

    printAll("Lora Inıtializing... ");

    std::vector<unsigned char> lora_return;
    int return_size;


        gmSerial.writeData("sys reset\r\n");
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

        lora_return.clear();
        usleep(1);


    do
    {
        gmSerial.writeData("radio set pwr ", 14, "\r\n");
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(1);

    }while( std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

    printAll("Lora radio set pwr 14 : ok");
    lora_return.clear();

    gmSerial.writeData("mac pause\r\n");
    gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

    printAll("Lora mac pause :", std::string(lora_return.begin(), lora_return.end()));
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set wdt ", 0, "\r\n" );
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(TRANSMISSION_TIMEOUT);
    }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

    printAll("Lora radio set wdt 0: ok");
    lora_return.clear();

    do
    {
        gmSerial.writeData("radio set freq ", gmFrequency, "\r\n" );
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(TRANSMISSION_TIMEOUT);

    }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

    printAll("Lora radio set freq ", gmFrequency, " : ok");
    lora_return.clear();

    do
    {

        gmSerial.writeData("radio set mod fsk\r\n" );
        gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);
        usleep(TRANSMISSION_TIMEOUT);
    }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n");

    printAll("Lora radio set mod fsk ok");
    lora_return.clear();


//    CheckListMutex.lock();
    try{
        CheckList["Lora"] = false;
    }
    catch(std::exception e)
    {
        printAll("e:", e.what());
    }

//    CheckListMutex.unlock();

    sleep(std::rand() % 10);
    
}



Status LoraWan::sendBeacon()
{

    std::string Data = prepareData();


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


    printAll("Lora sending beacon ");

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

                printAll("Lora Partial Data", partial_data);

                gmSerial.writeData(partial_data);

                lora_return.clear();
                gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

            }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\nradio_tx_ok\r\n");


        usleep(100000);

    }
}



void LoraWan::listenChannel()
{

    Status status;

    std::vector<unsigned char> lora_return;
    int return_size;
    std::string incoming_data;

    bool timeout = 0;

    printAll("Lora Listining Channel...");

    while(1)
    {
        do
        {

            do
            {

                lora_return.clear();
                gmSerial.writeData("radio rx 0\r\n");
                status = gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);

                printAll("Lora Incomming Data: ", std::string(lora_return.begin(), lora_return.end()));

            }while(std::string(lora_return.begin(), lora_return.end()) != "ok\r\n" &&
                   std::string(lora_return.begin(), lora_return.end()) != "busy\r\n");
            lora_return.clear();

            status = gmSerial.readData(lora_return, return_size = 0, TRANSMISSION_TIMEOUT);


            if(status == Status::time_out)
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
            printAll("Lora converting exception: ", exception.what());
            break;
        }

    }

    resetChannel();

    printAll("Lora Timeout!");

}



void LoraWan::resetChannel()
{
    std::string beacon = "hello";


    printAll("Lora Restarting...!");

    init();

    sendBeacon();

    listen();

}

std::string LoraWan::prepareData()
{

    std::string Data;
    int gps_char_pos;

    gmMutex.lock();

    try
    {
        Data = std::string(gmLoraStm.gps_string);
        gps_char_pos = Data.find_first_of("*");
        Data = Data.substr(0, gps_char_pos + 3);
        Data += "-" + std::to_string(gmLoraStm.gps_data.latitude);
        Data += "-" + std::string((const char *)&gmLoraStm.gps_data.ns_indicator);
        Data += "-" + std::to_string(gmLoraStm.gps_data.longnitude);
        Data += "-" + std::string((const char *)&gmLoraStm.gps_data.we_indicator);
        Data += "-" + std::to_string(gmLoraStm.sensor_data.temperature);
        Data += "-" + std::to_string(gmLoraStm.sensor_data.altitude);
        Data += "-" + std::to_string(gmLoraStm.sensor_data.pressure);
        Data += "-" + std::to_string(gmLoraStm.sensor_data.wheather_condition);
        Data += "-" + std::to_string(gmLoraStm.sensor_data.compass_degree);

        Data += "-" + std::to_string(gmLoraSfp.status);
        Data += "-" + std::to_string(gmLoraSfp.temperature);
        Data += "-" + std::to_string(gmLoraSfp.vcc);
        Data += "-" + std::to_string(gmLoraSfp.tx_bias);
        Data += "-" + std::to_string(gmLoraSfp.tx_power);
        Data += "-" + std::to_string(gmLoraSfp.rx_power);

        Data += "-end";
    }
    catch(std::exception ex)
    {
        printAll("Lora PrepareData exception: ",ex.what());
    }


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

    try
    {
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
    catch(std::exception ex)
    {
        printAll("Lora Data Collect Exception: ", ex.what());
    }



}

void LoraWan::listen()
{

    std::thread lora(&LoraWan::listenChannel, this);
    lora.detach();

}



void LoraWan::setLoraData(const SFP_DATA_FORMAT &SfpData, const ENVIRONMENT_DATA_FORMAT &StmData)
{

    gmMutex.lock();

    gmLoraSfp = SfpData;
    gmLoraStm = StmData;

    gmMutex.unlock();

}

void LoraWan::getLoraData(SFP_DATA_FORMAT &SfpData, ENVIRONMENT_DATA_FORMAT &StmData)
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

    try
    {
        while ((pos = CommingData.find(delimiter)) != std::string::npos)
        {

            if(i < 20)
            {
                token[i] = CommingData.substr(0, pos);
                CommingData.erase(0, pos + delimiter.length());
                i++;
            }
            else
                break;

        }


        gmMutex.lock();

        gmRecievedLoraStm.gps_string = token[0];

        try{
            gmRecievedLoraStm.gps_data.latitude = std::stod(token[1]);
            gmRecievedLoraStm.gps_data.ns_indicator = (unsigned char)*token[2].c_str();
            gmRecievedLoraStm.gps_data.longnitude = std::stod(token[3]);
            gmRecievedLoraStm.gps_data.we_indicator = (unsigned char)*token[4].c_str();
        }catch(std::exception ex)
        { printAll("Lora incoming gps_data exception: ", ex.what());}

        gmRecievedLoraStm.sensor_data.temperature = (uint32_t) std::stoi(token[5]);
        gmRecievedLoraStm.sensor_data.altitude = (uint32_t) std::stoi(token[6]);
        gmRecievedLoraStm.sensor_data.pressure = (uint32_t) std::stoi(token[7]);
        gmRecievedLoraStm.sensor_data.wheather_condition = (uint8_t) std::stoi(token[8]);
        gmRecievedLoraStm.sensor_data.compass_degree = (uint32_t) std::stoi(token[9]);

        gmRecievedLoraSfp.status = (int)std::stoi(token[10]);
        gmRecievedLoraSfp.temperature = (int)std::stoi(token[11]);
        gmRecievedLoraSfp.vcc = (int)std::stoi(token[12]);
        gmRecievedLoraSfp.tx_bias = (int)std::stoi(token[13]);
        gmRecievedLoraSfp.tx_power = (int)std::stoi(token[14]);
        gmRecievedLoraSfp.rx_power = (int)std::stoi(token[15]);



    }
    catch(std::exception ex)
    {
        printAll("Lora CallBack Exception: ",ex.what());
    }




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


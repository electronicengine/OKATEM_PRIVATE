#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>                    //Used for UART
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <time.h>
#include <globals.h>
#include <vector>
#include <sstream>
#include <mutex>

#include "globals.h"

#define TIMEOUT 50

class SerialCom
{



public:
    enum class Serial_Status
    {
        time_out,
        cannot_open,
        cannot_write,
        cannot_read,
        succesfully_opened,
        succesfully_written,
        succesfully_read
    }Status;


    SerialCom();
    SerialCom(const std::string& BaundRate);
    SerialCom(const std::string& BaundRate, const std::string& Port);

    template< typename T >
    inline std::string serializer(const T& t)
    {
        std::stringstream string_stream;
        string_stream << t;
        return string_stream.str();
    }

    template< typename T, typename ... Args >
    inline std::string serializer(const T& head, Args ... args)
    {
        return serializer( head ) + serializer( args... );
    }


    template<typename ...TAIL>
    Serial_Status writeData(const TAIL&... ContainerPack)
    {


        static std::vector<unsigned char> container_vector;
        std::string exploded_pack = serializer(ContainerPack...);

        int data_index = 0;
        int write_size = 0;

        unsigned char data;
        if (gmFileDescriptor != -1)
        {
            do
            {

                write_size = write(gmFileDescriptor, &(exploded_pack.c_str()[data_index]), sizeof(unsigned char));

                if(write_size != -1)
                  data_index += write_size;

            }while(data_index != exploded_pack.length());
        }
        else
        {
            printAll("Serial_Status::cannot_write\n");
            return Serial_Status::cannot_write;

        }
        return Serial_Status::succesfully_written;
    }


    Serial_Status readData(std::vector<unsigned char>& Container, int &Size, int Timeout);



private:
    std::string gmBaundRate;
    std::string gmPort;

    std::mutex gmMutex;
    int gmFileDescriptor;
    volatile short int gmTimeOutFlag = 0;
    volatile short int gmSetTime = 0;

    Serial_Status Init();
    void setTimeout(int TimeOut);
    Serial_Status Close();

//    virtual ~SerialCom();



};

#endif // SERIALCOM_H

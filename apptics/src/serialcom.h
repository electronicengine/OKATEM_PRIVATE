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
#include "queue.h"

#define TIMEOUT 50

class SerialCom
{



public:


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
    Status writeData(const TAIL&... ContainerPack)
    {

        std::string exploded_pack = serializer(ContainerPack...);

        std::vector<char> container_vector(exploded_pack.c_str(), exploded_pack.c_str() + exploded_pack.length());
        int data_index = 0;
        int write_size = 0;


        if(container_vector[container_vector.size() - 1] == ';')
        {
            container_vector.pop_back();
            container_vector.push_back(0xff);
            container_vector.push_back(0xff);
            container_vector.push_back(0xff);

        }

        if (gmFileDescriptor != -1)
        {

            do
            {

                write_size = write(gmFileDescriptor, &(container_vector[data_index]), sizeof(unsigned char));

                if(write_size != -1)
                  data_index += write_size;

            }while(data_index != container_vector.size());
        }
        else
        {
            printAll("Serial_Status::cannot_write");
            return Status::error;

        }
        return Status::ok;
    }


    Status readData(std::vector<unsigned char>& Container, int &Size, int Timeout);
    Status readData(std::vector<unsigned char>& Container, unsigned char Header, unsigned char Footer);



private:
    std::string gmBaundRate;
    std::string gmPort;

    std::mutex gmMutex;
    int gmFileDescriptor;
    volatile short int gmTimeOutFlag = 0;
    volatile short int gmSetTime = 0;

    Status Init();
    void setTimeout(int TimeOut);
    Status Close();

//    virtual ~SerialCom();



};

#endif // SERIALCOM_H

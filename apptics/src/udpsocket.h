#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <errno.h>             // For errno
#include <string.h>             // For memset
#include <thread>
#include <mutex>
#include <vector>

#include "controller.h"
#include "queue.h"
#include "fstream"

#define PORT            24000

#define FORWARD         1
#define BACKWARD        2

#define LISTENING_MODE  1
#define NORMAL_MODE     2



class UdpSocket
{

public:
    UdpSocket();
    ~UdpSocket();



    CONTROL_DATA_FORMAT getSocketControlData();

    UPDATE_FILE_FORMAT getSocketUpdateData();

    volatile int gmIsRecieved = 0;




    int sendData(UDP_DATA_FORMAT &UdpData, const std::string IpAddress);
    int sendData(INFORMATION_DATA_FORMAT &InformationData, const std::string IpAddress);
    int sendData(STREAM_DATA_FORMAT &StreamData, const std::string &IpAddress);
    int saveInformationData(CONTROL_DATA_FORMAT &ControlData, ENVIRONMENT_DATA_FORMAT &EnvironmentData, SFP_DATA_FORMAT &SfpData);

    std::vector<unsigned char> receiveData();

    int openPort(const std::string &IpAddress, int Port, int Mode);



private:

    int gmSocket;
    struct sockaddr_in gmClientAddr;
    struct sockaddr_in gmServerAddr;

    socklen_t gmClientLen = sizeof(gmServerAddr);

    std::string gmIpAddress;
    int gmPort;

    Queue<UPDATE_FILE_FORMAT> gmUpdateFileQueue;

    std::mutex gmMutex;
    SPI_TRANSFER_FORMAT gmSpiControlData;
    SPI_TRANSFER_FORMAT gmSpiUpdateData;

    void closePort();
    int openPort(int Port);

    CONTROL_DATA_FORMAT gmControlData;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentData;
    SFP_DATA_FORMAT gmSfpData;

    void listenPort();



};


#endif // UDPSOCKET_H

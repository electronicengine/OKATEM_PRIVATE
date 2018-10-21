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

#define PORT            24000

#define FORWARD         1
#define BACKWARD        2

#define LISTENING_MODE  1
#define NORMAL_MODE     2



class UdpSocket
{

public:
    UdpSocket();



    CONTROL_DATA_FORMAT getSocketControlData();

    UPDATE_FILE_FORMAT getSocketUpdateData();

    volatile int gmIsRecieved = 0;




    int sendData(SPI_TRANSFER_FORMAT &Data, const std::string IpAddress);
    int sendData(unsigned char* Data, const std::string &IpAddress);
    int sendData(int Data, const std::string &IpAddress);

    std::vector<unsigned char> receiveData();

    int openPort(int Port, int Mode);



private:

    int gmSocket;
    struct sockaddr_in gmClientAddr;
    struct sockaddr_in gmServerAddr;

    socklen_t gmClientLen = sizeof(gmServerAddr);
    int gmPort;


    Queue<UPDATE_FILE_FORMAT> gmUpdateFileQueue;

    std::mutex gmMutex;
    SPI_TRANSFER_FORMAT gmData;

    void closePort();
    int openPort(int Port);


    void listenPort();



};


#endif // UDPSOCKET_H

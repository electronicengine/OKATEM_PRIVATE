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

#include "globals.h"
#include "controller.h"

#define PORT 24000
#define DATA_SIZE 120



class UdpSocket
{

public:


    enum class UdpSocket_Status
    {
        time_out,
        error,
        ok
    }Status;


    UdpSocket();

    volatile int gmDataReady = 0;
    SPI_TX_FORMAT getSocketData();




private:

    int gmSocket;


    std::mutex gmMutex;
    SPI_TX_FORMAT gmData;

    void openPort();
    void closePort();

    void sendData();
    void recieveData();


};

#endif // UDPSOCKET_H

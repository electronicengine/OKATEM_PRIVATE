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
#include <string.h>            // For memset
#include <thread>
#include <mutex>
#include <vector>


#include "queue.h"
#include "ethernetsocket.h"
#include "globals.h"

#define PORT            24000

#define FORWARD         1
#define BACKWARD        2

#define LISTENING_MODE  1
#define NORMAL_MODE     2


class RemoteControlInterface;

class UdpSocket
{


public:

    UdpSocket();
    ~UdpSocket();

    volatile int gmIsRecieved = 0;

    void listen();
    void attach(RemoteControlInterface *Controller, void(RemoteControlInterface::*Func)(UDP_DATA_FORMAT&));


    int init(const std::string &IpAddress, int Port);

    int sendData(SPI_TRANSFER_FORMAT SpiData);
    int sendData(UDP_DATA_FORMAT &UdpData);
    int sendData(INFORMATION_DATA_FORMAT &InformationData);
    int sendData(STREAM_DATA_FORMAT &StreamData);
    int sendData(CAMERA_SETTINGS_FORMAT &CameraSettings);



private:

    Queue<STREAM_DATA_FORMAT> gmStreamDataQueue;
    std::mutex gmMutex;
    EthernetSocket gmEthernetSocket;
    RemoteControlInterface *gpController;
    void(RemoteControlInterface::*DataCallBackFunc)(UDP_DATA_FORMAT&);

    void listenPort();


};


#endif // UDPSOCKET_H

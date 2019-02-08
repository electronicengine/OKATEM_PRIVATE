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

#include "queue.h"
#include "ethernetsocket.h"

#define PORT            24000

#define FORWARD         1
#define BACKWARD        2

#define LISTENING_MODE  1
#define NORMAL_MODE     2


class SocketListener;
class RemoteController;
class VideoStream;

class UdpSocket
{


public:


    UdpSocket();
    ~UdpSocket();

    INFORMATION_DATA_FORMAT getInformationData();
    CONTROL_DATA_FORMAT getSocketControlData();
    UPDATE_FILE_FORMAT getSocketUpdateData();
    STREAM_DATA_FORMAT getStreamData();
    int getFeedBackCounter();

    void setFeedBackCounter(int Value);

    void attach(SocketListener *Observer);


    volatile int gmIsRecieved = 0;

    void listen();

    int init(const std::string &IpAddress, int Port);

    int sendData(SPI_TRANSFER_FORMAT SpiData);
    int sendData(UDP_DATA_FORMAT &UdpData);
    int sendData(INFORMATION_DATA_FORMAT &InformationData);
    int sendData(STREAM_DATA_FORMAT &StreamData);
    int saveInformationData(CONTROL_DATA_FORMAT &ControlData, ENVIRONMENT_DATA_FORMAT &EnvironmentData, SFP_DATA_FORMAT &SfpData);
    int setInitialMotorPositions(CONTROL_DATA_FORMAT &ControlData);

    int terminate();


private:

    Queue<UPDATE_FILE_FORMAT> gmUpdateFileQueue;
    Queue<STREAM_DATA_FORMAT> gmStreamDataQueue;

    std::mutex gmMutex;
    SPI_TRANSFER_FORMAT gmSpiControlData;
    SPI_TRANSFER_FORMAT gmSpiUpdateData;

    CONTROL_DATA_FORMAT gmControlData;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentData;
    SFP_DATA_FORMAT gmSfpData;
    INFORMATION_DATA_FORMAT gmInformationData;

    EthernetSocket gmEthernetSocket;

    void listenPort();

    int gmFeedBackCounter = 0;
    std::vector<SocketListener *> listeners;

    volatile bool gmTerminate = false;
    volatile bool gmTerminated = true;

};


#endif // UDPSOCKET_H

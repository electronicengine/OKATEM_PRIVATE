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

#define PORT 24000

#define FORWARD 1
#define BACKWARD 2



class UdpSocket
{

public:
    UdpSocket();



    CONTROL_DATA_FORMAT getSocketControlData();

    UPDATE_FILE_FORMAT getSocketUpdateData();

    volatile int gmIsRecieved = 0;


    void sendData(SPI_TRANSFER_FORMAT Data, const std::string& IpAddress);


private:

    int gmSocket;


    Queue<UPDATE_FILE_FORMAT> gmUpdateFileQueue;

    std::mutex gmMutex;
    SPI_TRANSFER_FORMAT gmData;

    void openPort();
    void closePort();


    void recieveData();


};


#endif // UDPSOCKET_H

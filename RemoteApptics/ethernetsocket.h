#ifndef ETHERNETSOCKET_H
#define ETHERNETSOCKET_H


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

#include "datatypes.h"

class EthernetSocket
{
public:
    EthernetSocket();
    ~EthernetSocket();

    int openSocket(const std::string &IpAddress, int Port);
    void closeSocket();

    int transferData(const std::vector<unsigned char> &Data);
    int recieveData(std::vector<unsigned char> &Data, unsigned int Size);


private:

    int gmSocket;
    struct sockaddr_in gmClientAddr;
    struct sockaddr_in gmServerAddr;

    socklen_t gmClientLen = sizeof(gmServerAddr);

    std::string gmIpAddress;
    int gmPort;
};

#endif // ETHERNETSOCKET_H

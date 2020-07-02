#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <net/route.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>       // For inet_addr()
#include <netinet/in.h>      // For sockaddr_in
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <memory.h>
#include <vector>
#include <fstream>

#define HOST_FILE           "/etc/hostname"
#define IPTABLE_RULES       "../iptables.sh"
#define GENMASK             "255.255.255.0"

#define ROMEO_HOST          "10.100.93.0"
#define ROMEO_WIFI_GATEWAY  "192.168.2.1"
#define ROMEO_SFP_GATEWAY   "192.168.1.2"

#define JULIET_HOST          "10.100.94.0"
#define JULIET_WIFI_GATEWAY  "192.168.2.2"
#define JULIET_SFP_GATEWAY   "192.168.1.1"


enum HOST
{
    Romeo,
    Juliet
};

class RoutingTable
{
public:
    RoutingTable();
    ~RoutingTable();
    int init();

    void switchSfp();
    void switchRF();

    const std::vector<std::string> HOST_NAMES = {"romeo", "juliet"};

private:
    void findHost();
    bool addRoute(const std::string &Destination, const std::string &GateWay, const std::string &GenMask);
    bool delRoute(const std::string &Destination, const std::string &GateWay, const std::string &GenMask);


    sockaddr_in *gpAddress;
    rtentry gmRoute;
    HOST gmHost;
    int gmFileDescriptor;


};

#endif // ROUTINGTABLE_H

#include "routingtable.h"
#include "globals.h"


RoutingTable::RoutingTable()
{

}

RoutingTable::~RoutingTable()
{
    close(gmFileDescriptor);
}

void RoutingTable::switchSfp()
{
    bool ret;

    switch (gmHost)
    {
        case Romeo:

            ret = delRoute(JULIET_HOST, ROMEO_WIFI_GATEWAY, GENMASK);
            if(ret == false)
                printAll("delroute has been faıled ");

            ret = addRoute(JULIET_HOST, ROMEO_SFP_GATEWAY, GENMASK);
            if(ret = false)
                printAll("addroute has been failed !!");



            std::cout << "Laser Host: " << ROMEO_SFP_GATEWAY
                      << " - " << GENMASK << std::endl;

            break;
        case Juliet:


            ret = delRoute(ROMEO_HOST, JULIET_WIFI_GATEWAY, GENMASK);
            if(ret == false)
                printAll("delroute has been failed !!");

            ret = addRoute(ROMEO_HOST, JULIET_SFP_GATEWAY, GENMASK);
            if(ret == false)
                printAll("addroute has been faıled ");

            std::cout << "Laser Host: " << JULIET_SFP_GATEWAY
                      << " - " << GENMASK << std::endl;

            break;

    }

    printAll("switchSfp!!!");
}

void RoutingTable::switchRF()
{
    bool ret;

    switch (gmHost)
    {
        case Romeo:

            ret = delRoute(JULIET_HOST, ROMEO_SFP_GATEWAY, GENMASK);
            if(ret == false)
                printAll("delroute has been failed !!");

            ret = addRoute(JULIET_HOST, ROMEO_WIFI_GATEWAY, GENMASK);
            if(ret == false)
                printAll("addroute has been failed !!");


            std::cout << "RF Host: " << ROMEO_WIFI_GATEWAY
                      << " - " << GENMASK << std::endl;

            break;
        case Juliet:

            ret = delRoute(ROMEO_HOST, JULIET_SFP_GATEWAY, GENMASK);
            if(ret == false)
                printAll("delroute has been faıled ");

            ret = addRoute(ROMEO_HOST, JULIET_WIFI_GATEWAY, GENMASK);
            if(ret == false)
                printAll("addroute has been failed !!");

            std::cout << "RF Host: " << JULIET_WIFI_GATEWAY
                      << " - " << GENMASK << std::endl;

            break;

    }

    printAll ("switchRF!!!");

}

int RoutingTable::init()
{
    printAll("Settings IP Tables Rules...");
    system(IPTABLE_RULES);
    findHost();

    gmFileDescriptor = socket( PF_INET, SOCK_DGRAM, IPPROTO_IP );

    if(gmFileDescriptor < 0)
    {
        printAll("Routing Table Driver File couldn't open!!!");
        return FAIL;
    }
    else
    {
        return SUCCESS;
    }

}

void RoutingTable::findHost()
{
    std::string host_name;
    std::ifstream myfile;

    myfile.open (HOST_FILE);
    myfile >> host_name;
    myfile.close();

    printAll("Host Name: ", host_name);

    if(host_name == HOST_NAMES[Romeo])
        gmHost = Romeo;
    else
        gmHost = Juliet;

}



bool RoutingTable::delRoute(const std::string &Destination, const std::string &GateWay, const std::string &GenMask)
{

   gpAddress = (sockaddr_in *) &gmRoute.rt_gateway;
   gpAddress->sin_family = AF_INET;
   gpAddress->sin_addr.s_addr = inet_addr(GateWay.c_str());

   gpAddress = (sockaddr_in *) &gmRoute.rt_dst;
   gpAddress->sin_family = AF_INET;
   gpAddress->sin_addr.s_addr = inet_addr(Destination.c_str());

   gpAddress = (sockaddr_in *) &gmRoute.rt_genmask;
   gpAddress->sin_family = AF_INET;
   gpAddress->sin_addr.s_addr = inet_addr(GenMask.c_str());

   gmRoute.rt_flags =  RTF_UP | RTF_GATEWAY ;
   gmRoute.rt_metric = 0;

   if (ioctl(gmFileDescriptor, SIOCDELRT, &gmRoute) < 0)
      return false;
   else
      return true;

}


bool RoutingTable::addRoute(const std::string &Destination, const std::string &GateWay, const std::string &GenMask)
{

    gpAddress = (sockaddr_in *) &gmRoute.rt_gateway;
    gpAddress->sin_family = AF_INET;
    gpAddress->sin_addr.s_addr = inet_addr(GateWay.c_str());

    gpAddress = (sockaddr_in *) &gmRoute.rt_dst;
    gpAddress->sin_family = AF_INET;
    gpAddress->sin_addr.s_addr = inet_addr(Destination.c_str());

    gpAddress = (sockaddr_in *) &gmRoute.rt_genmask;
    gpAddress->sin_family = AF_INET;
    gpAddress->sin_addr.s_addr = inet_addr(GenMask.c_str());

    gmRoute.rt_flags =  RTF_UP | RTF_GATEWAY ;
    gmRoute.rt_metric = 0;

   if (ioctl( gmFileDescriptor, SIOCADDRT, &gmRoute ) < 0)
      return false;
   else
       return true;

}

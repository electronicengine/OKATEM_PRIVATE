#include "routingtable.h"
#include "globals.h"


RoutingTable::RoutingTable()
{
    printAll("Settings IP Tables Rules...");
    system("../iptables.sh");
    findHost();

}

void RoutingTable::switchSfp()
{

    switch (gmHost)
    {
        case Romeo:

            delRoute(JULIET_HOST, ROMEO_WIFI_GATEWAY, GENMASK);
            addRoute(JULIET_HOST, ROMEO_SFP_GATEWAY, GENMASK);

            break;
        case Juliet:

//            delRoute(ROMEO_HOST, JULIET_WIFI_GATEWAY, GENMASK);
//            addRoute(ROMEO_HOST, JULIET_SFP_GATEWAY, GENMASK);

            break;

    }

    printAll("switchSfp!!!");
}

void RoutingTable::switchRF()
{
    switch (gmHost)
    {
        case Romeo:

            delRoute(JULIET_HOST, ROMEO_SFP_GATEWAY, GENMASK);
            addRoute(JULIET_HOST, ROMEO_WIFI_GATEWAY, GENMASK);

            break;
        case Juliet:

//            delRoute(ROMEO_HOST, JULIET_SFP_GATEWAY, GENMASK);
//            addRoute(ROMEO_HOST, JULIET_WIFI_GATEWAY, GENMASK);

            break;

    }

    printAll ("switchRF!!!");

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
   int fd = socket( PF_INET, SOCK_DGRAM, IPPROTO_IP );

   struct rtentry route;
   memset( &route, 0, sizeof( route ) );

   struct sockaddr_in *addr = (struct sockaddr_in *)&route.rt_gateway;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = inet_addr(GateWay.c_str());

   addr = (struct sockaddr_in*) &route.rt_dst;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = inet_addr(Destination.c_str());

   addr = (struct sockaddr_in*) &route.rt_genmask;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = inet_addr(GenMask.c_str());

   route.rt_flags = RTF_UP | RTF_GATEWAY;
   route.rt_metric = 0;

   // this time we are deleting the route:
   int ret = ioctl( fd, SIOCDELRT, &route );
   if ( ret )
   {
      close( fd );
      return false;
   }

   close( fd );
   return true;
}


bool RoutingTable::addRoute(const std::string &Destination, const std::string &GateWay, const std::string &GenMask)
{
   // create the control socket.
   int fd = socket( PF_INET, SOCK_DGRAM, IPPROTO_IP );

   struct rtentry route;
   memset( &route, 0, sizeof( route ) );

   // set the gateway to 0.
   struct sockaddr_in *addr = (struct sockaddr_in *)&route.rt_gateway;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = inet_addr(GateWay.c_str());

   // set the host we are rejecting.
   addr = (struct sockaddr_in*) &route.rt_dst;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = inet_addr(Destination.c_str());

   // you could use a less restrictive mask to block a range of IPs.
   // To block and entire C block you would use 255.255.255.0, or 0x00FFFFFFF
   addr = (struct sockaddr_in*) &route.rt_genmask;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = inet_addr(GenMask.c_str());

   // These flags mean: this route is created "up", or active
   // The blocked entity is a "host" as opposed to a "gateway"
   // The packets should be rejected. On BSD there is a flag RTF_BLACKHOLE
   // that causes packets to be dropped silently. We would use that if Linux
   // had it. RTF_REJECT will cause the network interface to signal that the
   // packets are being actively rejected.
   route.rt_flags = RTF_UP | RTF_GATEWAY;
   route.rt_metric = 0;

   // this is where the magic happens..
   if ( ioctl( fd, SIOCADDRT, &route ) )
   {
      close( fd );
      return false;
   }

   // remember to close the socket lest you leak handles.
   close( fd );
   return true;
}

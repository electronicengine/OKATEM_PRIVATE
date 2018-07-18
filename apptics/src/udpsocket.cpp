#include "udpsocket.h"

UdpSocket::UdpSocket()
{
    openPort();
}

SPI_TX_FORMAT UdpSocket::getSocketData()
{
    SPI_TX_FORMAT Data;

    gmMutex.lock();

    Data = gmData;
    gmData.clear();

    gmMutex.unlock();

    return Data;

}

void UdpSocket::openPort()
{

    struct sockaddr_in name;

    gmSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (gmSocket < 0)   {
    printAll("Opening datagram socket");
    }

    /* Bind our local address so that the client can send to us */
    bzero((char *) &name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    name.sin_port = htons(PORT);

    if (bind(gmSocket, (struct sockaddr *) &name, sizeof(name))) {
    printAll("binding datagram socket");
    }

    printAll("Socket has port number #%d\n", ntohs(name.sin_port));



}

void UdpSocket::closePort()
{

}

void UdpSocket::sendData()
{

}

void UdpSocket::recieveData()
{

    int ret;
    int package_size;

    unsigned char *ethernet_data;


        while(true)
        {

            package_size = read(gmSocket, ethernet_data, DATA_SIZE);
            if(package_size == DATA_SIZE)
            {

                gmMutex.lock();

                gmData = ethernet_data;

                gmMutex.unlock();

                delete []ethernet_data;

            }

        }

}

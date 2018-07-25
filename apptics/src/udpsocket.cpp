#include "udpsocket.h"
#include "globals.h"



UdpSocket::UdpSocket()
{
    openPort();
}

SPI_TX_FORMAT UdpSocket::getSocketData()
{
    SPI_TX_FORMAT Data;

    gmMutex.lock();

    if(gmDataReady == 1)
    {
        Data = gmData;
        gmDataReady = 0;
    }
    else
    {
        Data = FAIL;
    }

    gmMutex.unlock();

    return Data;

}

void UdpSocket::openPort()
{

    struct sockaddr_in name;

    gmSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (gmSocket < 0)   {
    printAll("Opening UdpSocket...");
    }

    /* Bind our local address so that the client can send to us */
    bzero((char *) &name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    name.sin_port = htons(PORT);

    if (bind(gmSocket, (struct sockaddr *) &name, sizeof(name))) {

    }
    else
    {
        printAll("UdpSocket can not bind...");
    }

    printAll("Socket has port number: ", ntohs(name.sin_port));

    std::thread listening_port(&UdpSocket::recieveData, this);
    listening_port.detach();


}

void UdpSocket::closePort()
{

}

void UdpSocket::sendData()
{

    struct sockaddr_in serv;

    unsigned char data[DATA_SIZE];

    data[0] = 12;
    data[1] = 13;
    data[2] = 14;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(24000);
//    serv.sin_addr.s_addr = inet_addr("10.100.93.14");

    socklen_t m = sizeof(serv);

    sendto(gmSocket, data, DATA_SIZE, 0, (struct sockaddr *)&serv, m);


}

void UdpSocket::recieveData()
{

    int ret;
    int package_size;

    unsigned char ethernet_data[DATA_SIZE];

    printAll("Listening UdpSocket...");

    while(true)
    {

        package_size = read(gmSocket, ethernet_data, DATA_SIZE);
        if(package_size == DATA_SIZE)
        {

            gmMutex.lock();

            gmData = ethernet_data;
            gmDataReady = 1;

            gmMutex.unlock();

        }

    }

}

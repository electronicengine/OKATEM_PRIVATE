#include "udpsocket.h"



UdpSocket::UdpSocket()
{
    openPort();
}

void UdpSocket::sendData(SPI_TRANSFER_FORMAT Data, const std::string &IpAddress)
{

    unsigned char *spi_data;

    struct sockaddr_in serv;
    ;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(24000);
    serv.sin_addr.s_addr = inet_addr(IpAddress.c_str());

    socklen_t m = sizeof(serv);

    spi_data = Data;

    sendto(gmSocket, spi_data, SPI_TRANSFER_SIZE, 0, (struct sockaddr *)&serv, m);

    delete [] spi_data;

}

CONTROL_DATA_FORMAT UdpSocket::getSocketControlData()
{
    CONTROL_DATA_FORMAT Data;

    gmMutex.lock();

    if(gmIsRecieved == 1)
    {
        if(gmData.header == 'C' | 'O' << 8)
        {
            Data = gmData;

        }
        else
        {
            Data = false;
        }

        gmIsRecieved = 0;
    }
    else
    {
        Data = false;
    }


    gmMutex.unlock();

    return Data;

}

UPDATE_FILE_FORMAT UdpSocket::getSocketUpdateData()
{

    UPDATE_FILE_FORMAT Data;

    gmMutex.lock();

    if(gmUpdateFileQueue.size() != 0)
    {

        Data = gmUpdateFileQueue.pop_front();

        Data.is_available = true;

        gmMutex.unlock();

        return Data;

    }
    else
    {
        Data.clear();
        gmMutex.unlock();

        return Data;
    }

}



void UdpSocket::openPort()
{

    struct sockaddr_in name;

    gmSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (gmSocket < 0)   {
    printAll("Opening datagram socket\r\n");
    }

    /* Bind our local address so that the client can send to us */
    bzero((char *) &name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    name.sin_port = htons(PORT);

    if (bind(gmSocket, (struct sockaddr *) &name, sizeof(name))) {
    printAll("binding datagram socket\r\n");
    }

    printf("Socket has port number %d\n\r", ntohs(name.sin_port));


    std::thread listening_port(&UdpSocket::recieveData, this);
    listening_port.detach();

}

void UdpSocket::closePort()
{

}


void UdpSocket::recieveData()
{

    int ret;
    int package_size;

    unsigned char *ethernet_data = new unsigned char[SPI_TRANSFER_SIZE];

    unsigned char *file_data = new unsigned char [SPI_ENTITY_SIZE * 405];


    while(true)
    {

        package_size = read(gmSocket, ethernet_data, SPI_TRANSFER_SIZE);

        if(package_size == SPI_TRANSFER_SIZE)
        {

            gmMutex.lock();

            gmData = ethernet_data;

            if((gmData.header & 0xff) == 'U' && ((gmData.header >> 8) & 0xff) == 'P')
            {

                UPDATE_FILE_FORMAT update_file;
                update_file = gmData;

                gmUpdateFileQueue.push_back(update_file);

            }

            if((gmData.header & 0xff) == 'C' && ((gmData.header >> 8) & 0xff) == 'O')
            {
                gmIsRecieved = 1;
            }

            gmMutex.unlock();

        }

    }
}

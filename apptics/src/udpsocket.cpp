#include "udpsocket.h"



UdpSocket::UdpSocket()
{
}


std::vector<unsigned char> UdpSocket::receiveData()
{

    int package_size;

    std::vector<unsigned char> data_container;
    unsigned char ethernet_data[STREAM_SIZE];

    package_size = read(gmSocket, ethernet_data, STREAM_SIZE);

    if(package_size <= STREAM_SIZE)
    {
       for(int i=0; i++; i<package_size)
           data_container.push_back(ethernet_data[i]);
    }

    return data_container;



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

int UdpSocket::sendData(SPI_TRANSFER_FORMAT &Data, const std::string IpAddress)
{

    unsigned char *spi_data;

    gmClientAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());

    spi_data = Data;

    sendto(gmSocket, spi_data, SPI_TRANSFER_SIZE, 0, (struct sockaddr *)&gmClientAddr, gmClientLen);

    delete [] spi_data;

}

int UdpSocket::sendData(unsigned char *Data, const std::string &IpAddress)
{

    gmClientAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    sendto(gmSocket, Data, STREAM_SIZE, 0, (struct sockaddr *)&gmClientAddr, gmClientLen);
}

int UdpSocket::sendData(int Data, const std::string &IpAddress)
{

    gmClientAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    sendto(gmSocket, &Data, sizeof(int), 0, (struct sockaddr *)&gmClientAddr, gmClientLen);

}

int UdpSocket::openPort(int Port)
{

    gmPort = Port;

    gmSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (gmSocket < 0)
    {
        printAll("cannot Open datagram socket!!\r\n");
        return FAIL;
    }


    /* Bind our local address so that the client can send to us */
    bzero((char *) &gmServerAddr, sizeof(gmServerAddr));
    gmServerAddr.sin_family = AF_INET;
    gmServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    gmServerAddr.sin_port = htons(Port);



    gmClientAddr.sin_family = AF_INET;
    gmClientAddr.sin_port = htons(gmPort);

    socklen_t gmClientLen= sizeof(gmClientAddr);


    if (bind(gmSocket, (struct sockaddr *) &gmServerAddr, sizeof(gmServerAddr)))
    {
        printAll("cannot bind datagram socket!!\r\n");
        return FAIL;
    }


    printAll("Socket has port number ", ntohs(gmServerAddr.sin_port));

    return SUCCESS;

}


int UdpSocket::openPort(int Port, int Mode)
{
    int ret;

    ret = openPort(Port);

    if(ret != SUCCESS)
        return FAIL;

    if(Mode == LISTENING_MODE)
    {
        std::thread listening_port(&UdpSocket::listenPort, this);
        listening_port.detach();

        return ret;
    }
    else
    {
        return ret;
    }

}

void UdpSocket::closePort()
{

}


void UdpSocket::listenPort()
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

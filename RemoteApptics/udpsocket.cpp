#include "udpsocket.h"



UdpSocket::UdpSocket()
{
}

UdpSocket::~UdpSocket()
{
    std::cout << "closing socket" << std::endl;
    close(gmSocket);
}


std::vector<unsigned char> UdpSocket::receiveData()
{

    int package_size;

    std::vector<unsigned char> data_container;
    unsigned char ethernet_data[ETHERNET_TRANSFER_SIZE];

    package_size = recv(gmSocket, ethernet_data, ETHERNET_TRANSFER_SIZE, 0);

    if(package_size == ETHERNET_TRANSFER_SIZE)
    {

       for(int i=0; i<package_size; i++)
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
        if(gmSpiControlData.header == (('C') | ('O' << 8)))
        {
            Data = gmSpiControlData;
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

//    gmMutex.lock();

//    if(gmUpdateFileQueue.size() != 0)
//    {

//        Data = gmUpdateFileQueue.pop_front();

//        Data.is_available = true;

//        gmMutex.unlock();

//        return Data;

//    }
//    else
//    {
//        Data.clear();
//        gmMutex.unlock();

//        return Data;
//    }

    return Data;

}

int UdpSocket::sendData(UDP_DATA_FORMAT &UdpData, const std::string IpAddress)
{


    unsigned char *raw_data;

    raw_data = UdpData;

    gmClientAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());

    sendto(gmSocket, raw_data, ETHERNET_TRANSFER_SIZE, 0, (struct sockaddr *)&gmClientAddr, gmClientLen);

    delete raw_data;

    return 0;


}

int UdpSocket::sendData(STREAM_DATA_FORMAT &StreamData, const std::string &IpAddress)
{
    UDP_DATA_FORMAT udp_data;

    unsigned char *raw_data;

    udp_data = StreamData;

    raw_data = udp_data;

    gmClientAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    sendto(gmSocket, raw_data, ETHERNET_TRANSFER_SIZE, 0, (struct sockaddr *)&gmClientAddr, gmClientLen);

    delete raw_data;

    return 0;
}

int UdpSocket::sendData(SPI_TRANSFER_FORMAT SpiData, const std::string &IpAddress)
{
    UDP_DATA_FORMAT udp_data;

    unsigned char *raw_data;


    udp_data = SpiData;

    raw_data = udp_data;

    gmClientAddr.sin_addr.s_addr = inet_addr(IpAddress.c_str());
    sendto(gmSocket, raw_data, ETHERNET_TRANSFER_SIZE, 0, (struct sockaddr *)&gmClientAddr, gmClientLen);

    delete raw_data;

    return 0;
}


int UdpSocket::openPort(int Port)
{

    int ret;
    struct timeval timeout;
    int optval = 1;
    gmPort = Port;

    gmSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (gmSocket < 0)
    {
        printf("cannot Open datagram socket!!\r\n");
        return FAIL;
    }


    /* Bind our local address so that the client can send to us */
    gmServerAddr.sin_family = AF_INET;
    gmServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    gmServerAddr.sin_port = htons(Port);



    gmClientAddr.sin_family = AF_INET;
    gmClientAddr.sin_port = htons(gmPort);

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    setsockopt(gmSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(gmSocket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    setsockopt(gmSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    ret = bind(gmSocket, (struct sockaddr *) &gmServerAddr, sizeof(gmServerAddr));
    if (ret)
    {
        printf("cannot bind datagram socket!! %d\r\n", ret);
        return FAIL;
    }


    printf("Socket has port number %d\r\n", ntohs(gmServerAddr.sin_port));

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

int UdpSocket::closePort()
{
    close(gmSocket);

    return SUCCESS;
}



void UdpSocket::listenPort()
{

    int package_size;

    SPI_TRANSFER_FORMAT spi_data;
    UDP_DATA_FORMAT udp_data;
    INFORMATION_DATA_FORMAT information_data;

    unsigned char *ethernet_data = new unsigned char[sizeof(UDP_DATA_FORMAT)];



    while(true)
    {


        package_size = read(gmSocket, ethernet_data, ETHERNET_TRANSFER_SIZE);

        if(package_size == ETHERNET_TRANSFER_SIZE)
        {

            gmMutex.lock();

            udp_data = ethernet_data;

            if(ethernet_data[0] == 'S' && ethernet_data[1] == 'P')
            {
                spi_data = (unsigned char *)udp_data.data;

                if((spi_data.header & 0xff) == 'U' && ((spi_data.header >> 8) & 0xff) == 'P')
                {

                    UPDATE_FILE_FORMAT update_file;

                    update_file = spi_data;

//                    gmUpdateFileQueue.push_back(update_file);

                }

                if((spi_data.header& 0xff) == 'C' && ((spi_data.header >> 8) & 0xff) == 'O')
                {
                    gmSpiControlData = spi_data;

                    gmIsRecieved = 1;
                }


            } else if(ethernet_data[0] == 'I' && ethernet_data[1] == 'N')
            {

                    //information data has been taken

            }else if(ethernet_data[0] == 'S' && ethernet_data[1] == 'T')
            {

                //stream data has been taken

            }


            gmMutex.unlock();

        }

    }
}

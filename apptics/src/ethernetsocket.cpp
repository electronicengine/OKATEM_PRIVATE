#include "ethernetsocket.h"

EthernetSocket::EthernetSocket()
{

}

EthernetSocket::~EthernetSocket()
{
    closeSocket();
}

int EthernetSocket::openSocket(const std::string &IpAddress, int Port)
{

    int ret;
    struct timeval timeout;
    int optval = 1;

    gmPort = Port;
    gmIpAddress = IpAddress;

    gmSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (gmSocket < 0)
    {
        std::cout << "cannot Open datagram socket!! Ip: " << IpAddress << " - Port " << std::to_string(Port) << std::endl;

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
        std::cout << "cannot bind datagram socket! Ip: " << IpAddress << " - Port " << std::to_string(Port) << std::endl;


        return FAIL;
    }


    std::cout << "Socket has been opened. Ip: " << IpAddress << " - Port " << std::to_string(Port) << std::endl;



    return SUCCESS;


}

void EthernetSocket::closeSocket()
{
    close(gmSocket);
}

int EthernetSocket::transferData(const std::vector<unsigned char> &Data)
{

    int transfered_size = 0;

    int data_size = Data.size();

    if(data_size != 0)
    {
        gmClientAddr.sin_addr.s_addr = inet_addr(gmIpAddress.c_str());

        transfered_size = sendto(gmSocket, (unsigned char *)Data.data(), data_size, 0, (struct sockaddr *)&gmClientAddr, gmClientLen);

        if(transfered_size == data_size)
        {
            return SUCCESS;
        }
        else
        {
            printf("Ethernet Data transfer problem");
            return FAIL;
        }

    }
    else
    {
        printf("Ethernet Data Size smaller than zero!");

        return FAIL;
    }

}

int EthernetSocket::recieveData(std::vector<unsigned char> &Data, int Size)
{

    int received_size = 0;

    if(Data.size() != Size)
        return FAIL;

    received_size = read(gmSocket, Data.data(), Size);

    if(received_size == Size)
       return SUCCESS;
    else
        return FAIL;

}

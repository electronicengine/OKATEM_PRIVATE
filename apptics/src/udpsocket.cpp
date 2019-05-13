#include "udpsocket.h"
#include "remotecontrolinterface.h"



UdpSocket::UdpSocket()
{
}




UdpSocket::~UdpSocket()
{
    gmEthernetSocket.closeSocket();
}




void UdpSocket::listen()
{
    std::thread listening_port(&UdpSocket::listenPort, this);
    listening_port.detach();
}

void UdpSocket::attach(RemoteControlInterface *Controller, void(RemoteControlInterface::*Func)(UDP_DATA_FORMAT&))
{
    gpController = Controller;
    DataCallBackFunc = Func;
}



int UdpSocket::init(const std::string &IpAddress, int Port)
{
   return gmEthernetSocket.openSocket(IpAddress, Port);
}



int UdpSocket::sendData(SPI_TRANSFER_FORMAT SpiData)
{
    std::vector<unsigned char> raw_data;

    UDP_DATA_FORMAT udp_data;

    udp_data = SpiData;

    raw_data = udp_data;

    return gmEthernetSocket.transferData(raw_data);
}



int UdpSocket::sendData(INFORMATION_DATA_FORMAT &InformationData)
{

    UDP_DATA_FORMAT udp_data;

    std::vector<unsigned char> raw_data;

    udp_data = InformationData;

    raw_data = udp_data;

    return gmEthernetSocket.transferData(raw_data);

}



int UdpSocket::sendData(STREAM_DATA_FORMAT &StreamData)
{

    UDP_DATA_FORMAT udp_data;
    std::vector<unsigned char> raw_data;

    udp_data = StreamData;

    raw_data = udp_data;

    return gmEthernetSocket.transferData(raw_data);

}



int UdpSocket::sendData(CAMERA_SETTINGS_FORMAT &CameraSettings)
{

    UDP_DATA_FORMAT udp_data;

    std::vector<unsigned char> raw_data;

    udp_data = CameraSettings;
    raw_data = udp_data;

    return gmEthernetSocket.transferData(raw_data);

}



int UdpSocket::sendData(UDP_DATA_FORMAT &UdpData)
{

    std::vector<unsigned char> raw_data;

    raw_data = UdpData;

    return gmEthernetSocket.transferData(raw_data);

}





void UdpSocket::listenPort()
{

    int ret;
    UDP_DATA_FORMAT udp_data;
    SPI_TRANSFER_FORMAT spi_data;

    std::vector<unsigned char> raw_data(ETHERNET_TRANSFER_SIZE);

    std::cout << "Udp Port Listening Thread Starting..." << std::endl;

    while(true)
    {

        ret = gmEthernetSocket.recieveData(raw_data, ETHERNET_TRANSFER_SIZE);

        if(ret == SUCCESS)
        {

            udp_data = raw_data;

            (gpController->*DataCallBackFunc)(udp_data);


        }

    }

}




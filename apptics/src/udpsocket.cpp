#include "udpsocket.h"

UdpSocket::UdpSocket()
{
}

UdpSocket::~UdpSocket()
{

    gmEthernetSocket.closeSocket();
}


CONTROL_DATA_FORMAT UdpSocket::getSocketControlData()
{
    CONTROL_DATA_FORMAT Data;

    if(gmIsRecieved == 1)
    {
        if(gmSpiControlData.header == 'C' | 'O' << 8)
        {
            printf("udp available\r\n");

            gmMutex.lock();
            Data = gmSpiControlData;
            gmMutex.unlock();

            Data.is_available = true;
        }
        else
        {
            Data.is_available = false;
            Data = false;
        }

        gmIsRecieved = 0;
    }
    else
    {
        Data.is_available = false;
        Data = false;
    }



    return Data;

}

UPDATE_FILE_FORMAT UdpSocket::getSocketUpdateData()
{

    UPDATE_FILE_FORMAT Data;


    if(gmUpdateFileQueue.size() != 0)
    {

        gmMutex.lock();
        Data = gmUpdateFileQueue.pop_front();
        gmMutex.unlock();

        Data.is_available = true;


        return Data;

    }
    else
    {
        Data.is_available = false;

        Data.clear();

        return Data;
    }

}


STREAM_DATA_FORMAT UdpSocket::getStreamData()
{
    STREAM_DATA_FORMAT Data;



    if(gmStreamDataQueue.size() != 0)
    {

        gmMutex.lock();
        Data = gmStreamDataQueue.pop_front();
        gmMutex.unlock();

        Data.is_available = true;


        return Data;

    }
    else
    {
        Data.is_available = false;

        Data.clear();

        return Data;
    }
}




void UdpSocket::listen()
{

    std::thread listening_port(&UdpSocket::listenPort, this);
    listening_port.detach();

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


    std::vector<unsigned char> raw_data;

    raw_data = StreamData;

    return gmEthernetSocket.transferData(raw_data);

}


int UdpSocket::sendData(UDP_DATA_FORMAT &UdpData)
{

    std::vector<unsigned char> raw_data;

    raw_data = UdpData;

    return gmEthernetSocket.transferData(raw_data);

}

int UdpSocket::saveInformationData(CONTROL_DATA_FORMAT &ControlData, ENVIRONMENT_DATA_FORMAT &EnvironmentData, SFP_DATA_FORMAT &SfpData)
{

    gmMutex.lock();

    gmControlData = ControlData;
    gmEnvironmentData = EnvironmentData;
    gmSfpData = SfpData;

    gmMutex.unlock();

    return 0;
}

int UdpSocket::setInitialMotorPositions(CONTROL_DATA_FORMAT &ControlData)
{
    gmMutex.lock();

    gmControlData = ControlData;

    gmMutex.unlock();

    return 0;

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



            if(raw_data[0] == 'S' && raw_data[1] == 'P')
            {
                spi_data = (unsigned char *)udp_data.data;

                if((spi_data.header & 0xff) == 'U' && ((spi_data.header >> 8) & 0xff) == 'P')
                {

                    UPDATE_FILE_FORMAT update_file;

                    update_file = spi_data;

                    gmMutex.lock();
                    gmUpdateFileQueue.push_back(update_file);
                    gmMutex.unlock();

                }

                if((spi_data.header& 0xff) == 'C' && ((spi_data.header >> 8) & 0xff) == 'O')
                {

                    gmMutex.lock();
                    gmSpiControlData = spi_data;

                    gmIsRecieved = 1;

                    gmMutex.unlock();

                }


            } else if(raw_data[0] == 'I' && raw_data[1] == 'N')
            {


                INFORMATION_DATA_FORMAT information_data;


               gmMutex.lock();

               information_data.control_data = gmControlData;
               information_data.sfp_data = gmSfpData;
               information_data.environment_data = gmEnvironmentData;

               gmMutex.unlock();


               sendData(information_data);


//                if(gmInformationData.is_available == false)
//                {
//                    gmInformationData = udp_data;
//                    gmInformationData.is_available = true;

//                }


            }
            else if(raw_data[0] == 'S' && raw_data[1] == 'T')
            {

                STREAM_DATA_FORMAT stream_data;

                stream_data = udp_data;

                gmMutex.lock();
                gmStreamDataQueue.push_back(stream_data);
                gmMutex.unlock();

            }


        }

    }
}

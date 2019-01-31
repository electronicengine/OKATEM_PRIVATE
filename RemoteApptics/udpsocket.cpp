#include "udpsocket.h"
#include "socketlistener.h"

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

    gmMutex.lock();

    if(gmIsRecieved == 1)
    {
        if(gmSpiControlData.header == ('C' | ('O' << 8)))
        {
            Data = gmSpiControlData;
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
        Data.is_available = false;

        Data.clear();
        gmMutex.unlock();

        return Data;
    }

}


INFORMATION_DATA_FORMAT UdpSocket::getInformationData()
{

    INFORMATION_DATA_FORMAT information_data;


    if(gmInformationData.is_available == true)
    {

        gmMutex.lock();

        information_data = gmInformationData;
        gmInformationData.is_available = false;

        gmMutex.unlock();


        information_data.is_available = true;

        return information_data;

    }
    else
    {
        information_data.is_available = false;

        return information_data;
    }




}

STREAM_DATA_FORMAT UdpSocket::getStreamData()
{
    STREAM_DATA_FORMAT Data;



    if(gmStreamDataQueue.size() != 0)
    {

        gmMutex.lock();

        Data = gmStreamDataQueue.pop_front();

        Data.is_available = true;

        gmMutex.unlock();

        return Data;

    }
    else
    {
        Data.is_available = false;

        Data.clear();

        return Data;
    }
}

int UdpSocket::getFeedBackCounter()
{
    int counter;

    gmMutex.lock();
    counter = gmFeedBackCounter;
    gmMutex.unlock();

    return counter;

}

void UdpSocket::setFeedBackCounter(int Value)
{
    gmMutex.lock();

    gmFeedBackCounter = Value;

    gmMutex.unlock();

}

void UdpSocket::attach(SocketListener *Observer)
{
    listeners.push_back(Observer);

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


//                    UPDATE_FILE_FORMAT update_file;

//                    update_file = spi_data;

//                    gmUpdateFileQueue.push_back(update_file);

                }

                if((spi_data.header& 0xff) == 'C' && ((spi_data.header >> 8) & 0xff) == 'O')
                {

//                    gmSpiControlData = spi_data;

//                    gmIsRecieved = 1;
                }


            } else if(raw_data[0] == 'I' && raw_data[1] == 'N')
            {


                if(gmInformationData.is_available == false)
                {
                    gmMutex.lock();
                    gmInformationData = udp_data;
                    gmInformationData.is_available = true;
                    gmMutex.unlock();
                }


            }else if(raw_data[0] == 'S' && raw_data[1] == 'T')
            {

                STREAM_DATA_FORMAT stream_data;

                stream_data = udp_data;

                gmMutex.lock();
                gmStreamDataQueue.push_back(stream_data);
                gmMutex.unlock();


            }
            else if(raw_data[0] == 'F' && raw_data[1] == 'E')
            {

                gmMutex.lock();
                gmFeedBackCounter++;
                gmMutex.unlock();


            }



            for(size_t i=0; i<listeners.size(); i++) // notify the subscribers
                listeners[i]->socketDataCheckCall();

        }

    }
}

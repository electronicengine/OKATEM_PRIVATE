#include "udpsocket.h"
#include "socketlistener.h"

UdpSocket::UdpSocket()
{
}

UdpSocket::~UdpSocket()
{


    gmTerminate = true;

    while(gmTerminated == false);

    if(gmEthernetSocket.isOpened() != SUCCESS)
        gmEthernetSocket.closeSocket();

}

bool UdpSocket::isEthernetConnected()
{
    bool condition;

    gmMutex.lock();
    if(gmTerminated == true)
        condition = false;
    else
        condition = true;

    gmMutex.unlock();

    return condition;
}


CONTROL_DATA_FORMAT UdpSocket::getSocketControlData()
{
    CONTROL_DATA_FORMAT Data;

    gmMutex.lock();

    if(gmIsRecieved == 1)
    {
        if(gmSpiControlData.header == SPI_TRANSFER_FORMAT::CONTROL_DATA)
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



CAMERA_SETTINGS_FORMAT UdpSocket::getCameraSettings()
{

    CAMERA_SETTINGS_FORMAT camera_settigs;


    if(gmCameraSettingsData.available == true)
    {
        gmMutex.lock();
        camera_settigs = gmCameraSettingsData;
        camera_settigs.available = true;
        gmMutex.unlock();

        gmCameraSettingsData.available = false;

        return camera_settigs;

    }
    else
    {
        camera_settigs.available = false;

        return camera_settigs;
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

    UDP_DATA_FORMAT udp_data;
    std::vector<unsigned char> raw_data;

    udp_data = StreamData;
    raw_data = udp_data;

    return gmEthernetSocket.transferData(raw_data);

}

int UdpSocket::sendData(CAMERA_SETTINGS_FORMAT CameraSettingsData)
{

    std::vector<unsigned char> raw_data;
    UDP_DATA_FORMAT udp_data;

    udp_data = CameraSettingsData;
    raw_data = udp_data;

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

int UdpSocket::terminate()
{

    gmTerminate = true;

    while(gmTerminated == false);

    if(gmEthernetSocket.isOpened() != SUCCESS)
        gmEthernetSocket.closeSocket();

    return SUCCESS;

}



void UdpSocket::listenPort()
{

    int ret;
    int timeout_counter = 0;

    UDP_DATA_FORMAT udp_data;

    std::vector<unsigned char> raw_data(ETHERNET_TRANSFER_SIZE);

    gmTerminated = false;

    std::cout << "Udp Port Listening Thread Starting..." << std::endl;


    while(true)
    {

        ret = gmEthernetSocket.recieveData(raw_data, ETHERNET_TRANSFER_SIZE);


        if(ret == SUCCESS)
        {

            udp_data = raw_data;

            switch (udp_data.header)
            {
                case UDP_DATA_FORMAT::SPI_DATA:

                    putSpiDataIntoBuffer(udp_data);

                    break;
                case UDP_DATA_FORMAT::INFORMATION_DATA:

                    putInformationDataIntoBuffer(udp_data);

                    break;

                case UDP_DATA_FORMAT::STREAM_DATA:

                    putStreamDataIntoBuffer(udp_data);

                    break;

                case UDP_DATA_FORMAT::FEEDBACK_DATA:

                    putFeedBackDataIntoBuffer(udp_data);

                    break;

                case UDP_DATA_FORMAT::CAMERA_SETTING_DATA:
                    putCameraSettingsIntoBuffer(udp_data);

                    break;

                default:
                    break;
            }


            for(size_t i=0; i<listeners.size(); i++) // notify the subscribers
                listeners[i]->socketDataCheckCall();

        }
        else
        {
            timeout_counter++;

            if(timeout_counter >= 4)
            {
                gmTerminated = true;

                timeout_counter = 0;

                for(size_t i=0; i<listeners.size(); i++) // notify the subscribers
                    listeners[i]->socketDataCheckCall();

                break;
            }
        }

        if(gmTerminate == true)
            break;

    }


    gmTerminated = true;

    std::cout << "Udp Socket Thread terminating... " << std::endl;

}

void UdpSocket::putInformationDataIntoBuffer(UDP_DATA_FORMAT &UdpData)
{

    if(gmInformationData.is_available == false)
    {

        gmMutex.lock();
        gmInformationData = UdpData;
        gmInformationData.is_available = true;
        gmMutex.unlock();

    }

}

void UdpSocket::putStreamDataIntoBuffer(UDP_DATA_FORMAT &UdpData)
{
    STREAM_DATA_FORMAT stream_data;

    stream_data = UdpData;

    gmMutex.lock();
    gmStreamDataQueue.push_back(stream_data);
    gmMutex.unlock();
}

void UdpSocket::putFeedBackDataIntoBuffer(UDP_DATA_FORMAT &UdpData)
{

    std::cout << "update feedback  " << UdpData.header << std::endl;

    gmMutex.lock();
    gmFeedBackCounter++;
    gmMutex.unlock();

}

void UdpSocket::putCameraSettingsIntoBuffer(UDP_DATA_FORMAT &UdpData)
{
    CAMERA_SETTINGS_FORMAT camera_settings;

    camera_settings = UdpData;

    gmMutex.lock();

    gmCameraSettingsData = camera_settings;
    gmCameraSettingsData.available  = true;

    gmMutex.unlock();
}

void UdpSocket::putSpiDataIntoBuffer(UDP_DATA_FORMAT &UdpData)
{

    SPI_TRANSFER_FORMAT spi_data;

    spi_data = (unsigned char *)UdpData.data;


    switch (spi_data.header) {
    case SPI_TRANSFER_FORMAT::CONTROL_DATA:

        //gmSpiControlData = spi_data;

        //gmIsRecieved = 1;

        break;

    case SPI_TRANSFER_FORMAT::ENVIRONMENT_DATA:


        break;

    case SPI_TRANSFER_FORMAT::UPDATE_FILE:

        //UPDATE_FILE_FORMAT update_file;

        //update_file = spi_data;

        //gmUpdateFileQueue.push_back(update_file);

        break;


    default:
        break;
    }


}

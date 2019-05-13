#include "remotecontrolinterface.h"
#include "udpsocket.h"
#include "mainoperation.h"
#include "driverinterface.h"
#include "environmentinterface.h"


RemoteControlInterface::RemoteControlInterface(MainOperation *Operation) : MainOperation(Operation)
{

    int ret;

    ret = gmControllerSocket.init(gpRemoteMachineInfo->stream_ip, gpRemoteMachineInfo->control_port);

    if(ret == SUCCESS)
        printAll("Controller Socket ip: ", gpRemoteMachineInfo->stream_ip, " port: ", std::to_string(gpRemoteMachineInfo->control_port));
    else
        printAll("Controller Socket can not be opened");

    gmControllerSocket.attach(this, &RemoteControlInterface::socketDataCallBack);
    gmControllerSocket.listen();

}

void RemoteControlInterface::socketDataCallBack(UDP_DATA_FORMAT &UdpData)
{

    switch (UdpData.header)
    {
        case UDP_DATA_FORMAT::SPI_DATA:

            processSpiData(UdpData);

            break;

        case UDP_DATA_FORMAT::INFORMATION_DATA:

            processInformationDataCallBack(UdpData);

            break;

        case UDP_DATA_FORMAT::CAMERA_SETTING_DATA:

            processCameraSettingsData(UdpData);

            break;

        case UDP_DATA_FORMAT::LASER_SWITCH_REQUEST:

            processWifiSwitch();

            break;
        case UDP_DATA_FORMAT::RF_SWITCH_REQUEST:

            processLaserSwitch();

            break;

        default:
            break;
    }

}


void RemoteControlInterface::processInformationDataCallBack(UDP_DATA_FORMAT &UdpData)
{

    int ret;
    INFORMATION_DATA_FORMAT information_data;

    information_data = gpDriverInterface->getInformationData();

    ret = gmControllerSocket.sendData(information_data);

    if(ret != SUCCESS)
        printAll("Information Data can not be sent!!!");

}



void RemoteControlInterface::processCameraSettingsData(UDP_DATA_FORMAT &UdpData)
{

    CAMERA_SETTINGS_FORMAT camera_settings;

    camera_settings = UdpData;

    camera_settings = gpDriverInterface->setCameraOptions(camera_settings);

    if(camera_settings.write_enable == 0)
        gmControllerSocket.sendData(camera_settings);

}


void RemoteControlInterface::processWifiSwitch()
{
    std::cout << "processWifiSwitch" << std::endl;
}

void RemoteControlInterface::processLaserSwitch()
{
    std::cout << "processLaserSwitch" << std::endl;
}



void RemoteControlInterface::processSpiData(UDP_DATA_FORMAT &UdpData)
{

    UDP_DATA_FORMAT feed_back_data;
    SPI_TRANSFER_FORMAT spi_data;
    UPDATE_FILE_FORMAT update_file;
    CONTROL_DATA_FORMAT control_data;

    spi_data = (unsigned char *)UdpData.data;


    switch (spi_data.header)
    {
        case SPI_TRANSFER_FORMAT::CONTROL_DATA:

            control_data = spi_data;

            gpDriverInterface->driveStmBoard(control_data);

            break;

        case SPI_TRANSFER_FORMAT::UPDATE_FILE:


            update_file = spi_data;

            gpDriverInterface->updateStmBoard(update_file);

            feed_back_data.header = UDP_DATA_FORMAT::FEEDBACK_DATA;
            gmControllerSocket.sendData(feed_back_data);

            break;


        default:
            break;
    }

}





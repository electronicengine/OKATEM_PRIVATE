#ifndef REMOTECONTROLINTERFACE_H
#define REMOTECONTROLINTERFACE_H

#include "mainoperation.h"


class UdpSocket;



class RemoteControlInterface : public MainOperation
{

public:
    RemoteControlInterface(MainOperation *Operation);
    void socketDataCallBack(UDP_DATA_FORMAT &UdpData);
private:
    UdpSocket gmControllerSocket;

    void processSpiData(UDP_DATA_FORMAT &UdpData);
    void processInformationDataCallBack(UDP_DATA_FORMAT& UdpData);
    void processCameraSettingsData(UDP_DATA_FORMAT& UdpData);
    void processWifiSwitch();
    void processLaserSwitch();

};

#endif // REMOTECONTROLINTERFACE_H

#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <fstream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>


#include "socketlistener.h"
#include "udpsocket.h"
#include "datatypes.h"
#include <QApplication>



#define WIDTH 30
#define HEIGHT 10

#define MAX_STEPMOTOR_SPEED 60
#define FORWARD 1
#define BACKWARD 2
#define STOP 0



class MainWindow;
class DisplayPanel;

enum Direction
{
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight,
    stop
};


class RemoteController : public SocketListener
{

public:

    RemoteController(UdpSocket *Socket);
    virtual ~RemoteController();

    int start(const std::string &IpAddress, int Port, DisplayPanel *DisplayWindow);

    std::vector<unsigned char> readFile(const std::string &FileName);
    void parseAndSendData(std::vector<unsigned char> &Container, const std::string &IpAddress);

    void servo1SetValue(int Value);
    void servo2SetValue(int Value);

    void stop();
    void turnLeft();
    void turnRight();
    void turnDown();
    void turnUp();

    void setCalibrationValues(const CONTROL_DATA_FORMAT &CalibrationValues);

    void setStep1Speed(int value, int Max);
    void setStep2Speed(int value, int Max);

    void updateFirmware(const std::string &FileName);

    int resetUpdatePercentage();
    int sendCameraSettingsRequest(const CAMERA_SETTINGS_FORMAT& CameraSettings);
    int sendInformationRequest();
    int gotoPositions(uint32_t XPosition, uint32_t YPosition);
    int turntoDirection(uint32_t DirectionCommand, uint32_t Duration);

    CONTROL_DATA_FORMAT getControlData();
    void socketDataCheckCall();

    int terminate();


private:

    DisplayPanel *gpDisplayPanel;

    UdpSocket *gpSocket;


    volatile int gmUpdatePercentage = 0;
    volatile bool gmTerminate = false;
    volatile bool gmTerminated = true;

    int gmUpdateFileSequence;

    std::string gmIpAddress;
    std::string gmPort;
    CONTROL_DATA_FORMAT gmTxData;
    CONTROL_DATA_FORMAT gmControlSignal;

    INFORMATION_DATA_FORMAT gmInformationData;

    std::mutex gmMutex;
    std::mutex gmControlSignalMutex;

    void updateThread(const std::string &FileName);
    void updateThreadTerminated();

};



#endif // CONTROLLER_H

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

#define MAX_STEPMOTOR_SPEED 1
#define MAX_INVERSE_SPEED_VALUE 20
#define FORWARD 1
#define BACKWARD 2
#define STOP 0



class MainWindow;


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


    int start(const std::string &IpAddress, int Port);

    std::vector<unsigned char> readFile(const std::string &FileName);
    void parseAndSendData(std::vector<unsigned char> &Container, const std::string &IpAddress);

    void run(const std::string &IpAddress, int Port);
    void runController(const std::string &IpAddress, int Port);

    void servo1SetValue(int Value);
    void servo2SetValue(int Value);


    void stop();
    void turnLeft();
    void turnRight();
    void turnDown();
    void turnUp();

    void setCalibrationValues(const CONTROL_DATA_FORMAT &CalibrationValues);
    void increaseSpeed();
    void decreaseSpeed();
    void setSpeed(int value);

    void updateFirmware(const std::string &FileName);

    int getFsoInformations(CONTROL_DATA_FORMAT &ControlData, ENVIRONMENT_DATA_FORMAT &EnvironmentData, SFP_DATA_FORMAT &SfpData);
    int getUpdatePercentage();
    int resetUpdatePercentage();
    int gotoPositions(uint32_t XPosition, uint32_t YPosition);
    int turntoDirection(uint32_t DirectionCommand, uint32_t Duration);

    void socketDataCheckCall();

    int terminate();


private:


    UdpSocket *gpSocket;

    int gmServoMotor1Degree = 50;
    int gmServoMotor2Degree = 50;

    int gmUpdatePercentage = 0;

    volatile bool gmTerminate = false;
    volatile bool gmTerminated = true;

    volatile bool gmUploadingStart = false;

    int gmUpdateFileSequence;
    int gmSpeed = 1;
    std::string gmIpAddress;
    std::string gmPort;
    CONTROL_DATA_FORMAT gmTxData;


    INFORMATION_DATA_FORMAT gmInformationData;

    std::mutex gmMutex;

    void updateThread(const std::string &FileName);
    void updateThreadTerminated();

};



#endif // CONTROLLER_H

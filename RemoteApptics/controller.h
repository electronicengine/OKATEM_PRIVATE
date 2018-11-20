#ifndef CONTROLLER_H
#define CONTROLLER_H


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

#include "udpsocket.h"
#include "datatypes.h"

#define WIDTH 30
#define HEIGHT 10

#define MAX_SPEED 20


class Controller
{

public:
    Controller();


    int start(const std::string &IpAddress, int Port);

    std::vector<unsigned char> readFile(const std::string &FileName);
    void parseAndSendData(std::vector<unsigned char> &Container, const std::string &IpAddress);

    void run(const std::string &IpAddress, int Port);
    void runController(const std::string &IpAddress, int Port);

    void servo1SetValue(int Value);
    void servo2SetValue(int Value);

    void servo1Forward();
    void servo1Backward();
    void servo2Forward();
    void servo2Backward();

    void turnLeft();
    void turnRight();
    void turnDown();
    void turnUp();

    void increaseSpeed();
    void decreaseSpeed();
    void setSpeed(int value);

    void updateFirmware(const std::string &FileName);

    int getFsoInformations(CONTROL_DATA_FORMAT &ControlData, ENVIRONMENT_DATA_FORMAT &EnvironmentData, SFP_DATA_FORMAT &SfpData);


private:


    UdpSocket gmSocket;

    int gmServoMotor1Degree = 50;
    int gmServoMotor2Degree = 50;

    int gmSpeed = 1;
    std::string gmIpAddress;
    std::string gmPort;

    CONTROL_DATA_FORMAT gmTxData;


};

#endif // CONTROLLER_H

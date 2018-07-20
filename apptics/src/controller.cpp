#include "controller.h"
#include "globals.h"

Controller::Controller()
{

    std::thread communication(&Controller::communicationThread, this);
    communication.detach();
}

Controller::~Controller()
{

}

Controller::Controller_Status Controller::zoomInCamera()
{

    gmMutex.lock();
    gmBPIControlData.servo_motor1_degree= 120;
    gmBPIControlData.servo_motor1_direction = FORWARD;
    gmMutex.unlock();

    return Controller_Status::ok;

}


Controller::Controller_Status Controller::zoomOutCamera()
{

    gmMutex.lock();
    gmBPIControlData.servo_motor1_degree = 120;
    gmBPIControlData.servo_motor1_direction = BACKWARD;
    gmMutex.unlock();

    return Controller_Status::ok;
}

Controller::Controller_Status Controller::driveMotorLeft()
{

    gmMutex.lock();
    gmBPIControlData.step_motor2_direction = FORWARD;
    gmBPIControlData.step_motor2_speed = 36;
    gmMutex.unlock();

    return Controller_Status::ok;
}



Controller::Controller_Status Controller::driveMotorRight()
{

    gmMutex.lock();
    gmBPIControlData.step_motor2_direction = BACKWARD;
    gmBPIControlData.step_motor2_speed = 87;
    gmMutex.unlock();

    return Controller_Status::ok;
}




Controller::Controller_Status Controller::driveMotorUp()
{
    gmMutex.lock();
    gmBPIControlData.step_motor1_direction = FORWARD;
    gmBPIControlData.step_motor1_speed = 45;
    gmMutex.unlock();

    return Controller_Status::ok;
}


Controller::Controller_Status Controller::driveMotorDown()
{
    gmMutex.lock();
    gmBPIControlData.step_motor1_direction = BACKWARD;
    gmBPIControlData.step_motor1_speed = 5;
    gmMutex.unlock();

    return Controller_Status::ok;
}



Controller::Controller_Status Controller::setControlData(SPI_TX_FORMAT Data)
{
    gmMutex.lock();

    gmBPIControlData = Data;

    gmMutex.unlock();

    return Controller_Status::ok;
}

SPI_RX_FORMAT Controller::getStmEnvironment()
{
    SPI_RX_FORMAT Data;

    gmMutex.lock();
    Data = gmStmEnvironmentData;
    gmMutex.unlock();

    return Data;
}

void Controller::communicationThread()
{

    unsigned char *transmitted_data;

    while(true)
    {


        try
        {
            gmMutex.lock();

            transmitted_data = (unsigned char *)gmBPIControlData;

            gmSpi.spiTransmiteReceive((unsigned char *)transmitted_data, SPI_TRANSFER_SIZE);

            gmStmEnvironmentData = (unsigned char *)transmitted_data;
            delete []transmitted_data;
            gmBPIControlData.clear();


        }
        catch(std::exception ex)
        {
            printAll(ex.what());
        }


        gmMutex.unlock();


        usleep(100000);


    }


}

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

Controller::Controller_Status Controller::isReady()
{

    if(gmIsTransmitted)
    {
        return Controller_Status::ok;
    }
    else
    {
        return Controller_Status::error;
    }

}



Controller::Controller_Status Controller::zoomInCamera()
{


    gmControlData.servo_motor1_degree= 120;
    gmControlData.servo_motor1_direction = FORWARD;

    gmMutex.lock();

    gmSpiTxData = gmControlData;

    gmMutex.unlock();

    return Controller_Status::ok;

}



Controller::Controller_Status Controller::zoomOutCamera()
{

    gmControlData.servo_motor1_degree = 120;
    gmControlData.servo_motor1_direction = BACKWARD;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Controller_Status::ok;
}

Controller::Controller_Status Controller::driveMotorLeft()
{

    gmControlData.step_motor2_direction = FORWARD;
    gmControlData.step_motor2_speed = 36;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Controller_Status::ok;
}



Controller::Controller_Status Controller::driveMotorRight()
{

    gmControlData.step_motor2_direction = BACKWARD;
    gmControlData.step_motor2_speed = 87;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Controller_Status::ok;
}



Controller::Controller_Status Controller::driveMotorUp()
{

    gmControlData.step_motor1_direction = FORWARD;
    gmControlData.step_motor1_speed = 45;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Controller_Status::ok;
}


Controller::Controller_Status Controller::driveMotorDown()
{


    gmControlData.step_motor1_direction = BACKWARD;
    gmControlData.step_motor1_speed = 5;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Controller_Status::ok;

}



Controller::Controller_Status Controller::setControlData(CONTROL_DATA_FORMAT& Data)
{
    gmMutex.lock();

    gmSpiTxData = Data;

    gmMutex.unlock();

    return Controller_Status::ok;
}

Controller::Controller_Status Controller::setUpdateData(UPDATE_FILE_FORMAT &Data)
{

//    static unsigned char *file_data = new unsigned char [43644];


//    if(Data.current_sequence_number == Data.total_sequence_number)
//    {
//        for(int i=0; i<43644 % SPI_ENTITY_SIZE; i++)
//        {
//            file_data[i + (SPI_ENTITY_SIZE * (Data.current_sequence_number - 1))] = Data.data[i];
//        }


//        FILE *write_ptr;

//        write_ptr = fopen("test.bin","wb");  // w for write, b for binary

//        fwrite(file_data,43644,1,write_ptr); // write 10 bytes from our buffer

//        fclose(write_ptr);

//        delete [] file_data;
//    }
//    else
//    {
//        for(int i=0;i<SPI_ENTITY_SIZE; i++)
//        {
//            file_data[i + (SPI_ENTITY_SIZE * (Data.current_sequence_number - 1))] = Data.data[i];
//        }
//    }





//    return Controller_Status::ok;

    if(gmIsTransmitted)
    {

        gmMutex.lock();

        gmSpiTxData = Data;

        std::cout << Data.current_sequence_number << "/" << Data.total_sequence_number << "\r" << std::endl;

        gmIsTransmitted = false;

        gmMutex.unlock();

        return Controller_Status::ok;
    }
    else
    {
        return Controller_Status::error;
    }

}

ENVIRONMENT_DATA_FORMAT Controller::getStmEnvironment()
{

    gmMutex.lock();

    if(gmIsReceived)
    {
        gmIsReceived = false;
        gmEnvironmentData = gmSpiRxData;
    }

    gmMutex.unlock();

    return gmEnvironmentData;
}

void Controller::communicationThread()
{


    unsigned char *spi_transfer_data;
    int wait_time = 100000;

    SpiCom::Spi_Status status;


    printAll("Stm Spi Communication Thread Starting...");

    while(true)
    {

        gmMutex.lock();

            spi_transfer_data = gmSpiTxData;

            if((gmSpiTxData.header & 0xff) == 'C' && ((gmSpiTxData.header >> 8) & 0xff) == 'O')
            {
                wait_time = 100000;
            }
            else if((gmSpiTxData.header & 0xff) == 'U' && ((gmSpiTxData.header >> 8) & 0xff) == 'P')
            {
                wait_time = 150000;
                std::cout << "UP" << std::endl;
            }

            status = gmSpi.spiTransmiteReceive(spi_transfer_data, SPI_TRANSFER_SIZE);

            if(status == SpiCom::Spi_Status::succesfully_writeread)
            {
                gmSpiRxData = spi_transfer_data;
                gmSpiTxData.clear();
                gmIsTransmitted = true;
                gmIsReceived = true;
            }
            else
            {

                gmSpiRxData.clear();
                gmSpiTxData.clear();
                gmIsTransmitted = false;
                gmIsReceived = false;

            }



        gmMutex.unlock();


        usleep(wait_time);


    }


}

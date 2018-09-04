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

    static int percent = 0;
    static int last_percent;

    if(gmIsTransmitted)
    {

        gmMutex.lock();

        if(gmDesiredPackageSequence >= gmCurrentPackageSequence)
        {
           gmUpdateFile = Data;

           gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

           gmSpiTxData = gmUpdateFile;

           gmIsTransmitted = false;

           gmMutex.unlock();


           percent = (int)(((double)gmUpdateFile.current_sequence_number/Data.total_sequence_number) * 100);

           if(percent != last_percent)
           std::cout << "Update file %" << percent << " is uploaded. " << "\r" << std::endl;

            last_percent = percent;


           return Controller_Status::ok;

        }
        else
        {

            gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

            gmSpiTxData = gmUpdateFile;

            gmIsTransmitted = false;

            gmMutex.unlock();

            return Controller_Status::error;

        }

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


    UPDATE_FILE_FORMAT update_file;
    UPDATE_FILE_FORMAT backup_update_file;

    SpiCom::Spi_Status status;


    printAll("Stm Spi Communication Thread Starting...");

    while(true)
    {

        gmMutex.lock();

        spi_transfer_data = gmSpiTxData;

        status = gmSpi.spiTransmiteReceive(spi_transfer_data, SPI_TRANSFER_SIZE);

        if(status == SpiCom::Spi_Status::succesfully_writeread)
        {
           gmSpiRxData = spi_transfer_data;


            if(spi_transfer_data[0] == 'U' && spi_transfer_data[1] == 'P')
            {
                gmDesiredPackageSequence = spi_transfer_data[2] | (spi_transfer_data[3] << 8) |
                        (spi_transfer_data[4] << 16) | (spi_transfer_data[5] << 24);

                if((gmDesiredPackageSequence < gmCurrentPackageSequence))
                {
                    gmSpiTxData = gmBackupUpdateFile;
                    gmCurrentPackageSequence = gmBackupUpdateFile.current_sequence_number;

                    gmSpiRxData.clear();
                    gmIsTransmitted = false;
                    gmIsReceived = true;

                }
                else if((gmDesiredPackageSequence > gmCurrentPackageSequence))
                {

                    gmSpiRxData.clear();
                    gmIsTransmitted = true;
                    gmIsReceived = true;

                }else if(((gmDesiredPackageSequence == gmCurrentPackageSequence)))
                {
                    gmBackupUpdateFile = gmUpdateFile;
                    gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

                    gmSpiRxData.clear();
                    gmIsTransmitted = true;
                    gmIsReceived = true;

                }

            }
            else
            {
                gmSpiRxData.clear();
                gmIsTransmitted = true;
                gmIsReceived = true;
            }

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

#include "controller.h"
#include "globals.h"

extern std::map<const std::string, bool> CheckList;

Controller::Controller()
{

    CheckList.insert(std::make_pair<std::string, bool>("Controller", true));

    std::thread communication(&Controller::communicationThread, this);
    communication.detach();

}



Controller::~Controller()
{

}



Status Controller::isReady()
{

    if(gmIsTransmitted)
    {
        return Status::ok;
    }
    else
    {
        return Status::error;
    }

}



Status Controller::zoomInCamera()
{


    gmControlData.servo_motor1_degree= 120;
    gmControlData.servo_motor1_direction = FORWARD;

    gmMutex.lock();

    gmSpiTxData = gmControlData;

    gmMutex.unlock();

    return Status::ok;

}



Status Controller::zoomOutCamera()
{

    gmControlData.servo_motor1_degree = 120;
    gmControlData.servo_motor1_direction = BACKWARD;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status Controller::driveMotorLeft()
{

    gmControlData.step_motor2_direction = FORWARD;
    gmControlData.step_motor2_speed = 36;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status Controller::driveMotorRight()
{

    gmControlData.step_motor2_direction = BACKWARD;
    gmControlData.step_motor2_speed = 87;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status Controller::driveMotorUp()
{

    gmControlData.step_motor1_direction = FORWARD;
    gmControlData.step_motor1_speed = 45;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status Controller::driveMotorDown()
{

    gmControlData.step_motor1_direction = BACKWARD;
    gmControlData.step_motor1_speed = 5;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;

}



Status Controller::setControlData(CONTROL_DATA_FORMAT& Data)
{

    gmMutex.lock();

    gmSpiTxData = Data;

    gmMutex.unlock();

    return Status::ok;

}



Status Controller::setUpdateData(UPDATE_FILE_FORMAT &Data)
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

             std::cout << "set" << std::endl;

             gmSpiTxData = gmUpdateFile;

             gmIsTransmitted = false;

             gmMutex.unlock();

             percent = (int)(((double)gmUpdateFile.current_sequence_number/Data.total_sequence_number) * 100);

             if(percent != last_percent)
              printAll("Update file %", percent, " is uploaded. ");

              last_percent = percent;


             return Status::ok;

          }
          else
          {

              gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

              gmSpiTxData = gmUpdateFile;

              gmIsTransmitted = false;

              gmMutex.unlock();

              return Status::error;

          }

      }
      else
      {
          return Status::error;
      }




}



ENVIRONMENT_DATA_FORMAT Controller::getStmEnvironment()
{

    ENVIRONMENT_DATA_FORMAT data;

    gmMutex.lock();

    if(gmIsReceived)
    {

        gmIsReceived = false;
        data = gmEnvironmentData;
    }

    gmMutex.unlock();

    return data;
}



void Controller::communicationThread()
{


    bool spi_is_working = false;
    unsigned char *spi_transfer_data;
    int wait_time = 100000;

    Status status;



    printAll("Stm Spi Communication Thread Starting...");

    while(true)
    {

        gmMutex.lock();

        spi_transfer_data = gmSpiTxData;

        status = gmSpi.spiTransmiteReceive(spi_transfer_data, SPI_TRANSFER_SIZE);

        if(status == Status::ok)
        {
           gmSpiRxData = spi_transfer_data;

            status = checkIfUpdateData(gmSpiRxData);
            if(status == Status::ok)
            {
               gmIsTransmitted = true;
               gmIsReceived = true;

            }
            else if(status == Status::time_out)
            {
                gmIsTransmitted = false;
                gmIsReceived = false;
            }
            else
            {
                status = checkIfEnvironmentData(gmSpiRxData);
                if(status == Status::ok)
                {

                    gmIsReceived = true;
                    gmIsTransmitted = true;
                }
                else
                {

                    gmIsTransmitted = false;
                    gmIsReceived = false;
                }

                gmSpiTxData.clear();

            }


            CheckList["Controller"] = true;

        }
        else
        {

            gmSpiTxData.clear();

            gmSpiRxData.clear();
            gmSpiTxData.clear();
            gmIsTransmitted = false;
            gmIsReceived = false;

            CheckList["Controller"] = false;

        }

        gmMutex.unlock();

        usleep(wait_time);


    }

}



Status Controller::checkIfUpdateData(const SPI_TRANSFER_FORMAT& SpiData)
{

    UPDATE_FILE_FORMAT file_package_response;

    if((SpiData.header & 0xff) == 'U' && ((SpiData.header >> 8) & 0xff) == 'P')
    {

        file_package_response = SpiData;
        gmDesiredPackageSequence = file_package_response.current_sequence_number;



        if((gmDesiredPackageSequence < gmCurrentPackageSequence))
        {

            printAll(gmDesiredPackageSequence, "<", gmCurrentPackageSequence);
//             std::cout << gmDesiredPackageSequence << "<" << gmCurrentPackageSequence << std::endl;

            gmSpiTxData = gmBackupUpdateFile;

            gmCurrentPackageSequence = gmBackupUpdateFile.current_sequence_number;

//            std::cout << gmDesiredPackageSequence << "<=" << gmCurrentPackageSequence << std::endl;

            gmIsTransmitted = false;

            gmSpiRxData.clear();

            return Status::time_out;


        }
        else if((gmDesiredPackageSequence > gmCurrentPackageSequence))
        {

            printAll(gmDesiredPackageSequence, ">", gmCurrentPackageSequence);
//            std::cout << gmDesiredPackageSequence << ">" << gmCurrentPackageSequence << std::endl;

            gmSpiRxData.clear();

            return Status::ok;


        }
        else if(((gmDesiredPackageSequence == gmCurrentPackageSequence)))
        {

            printAll(gmDesiredPackageSequence, "==", gmCurrentPackageSequence);
//             std::cout << gmDesiredPackageSequence << "==" << gmCurrentPackageSequence << std::endl;

            gmBackupUpdateFile = gmUpdateFile;
            gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

            if(gmCurrentPackageSequence == gmUpdateFile.total_sequence_number)
            {
                printAll("Firmware Updating is done");
                gmUpdateFile.clear();
                gmSpiTxData.clear();

                return Status::error;
            }

            gmSpiRxData.clear();

            return Status::ok;

        }

    }
    else
    {
        return Status::error;
    }

}



Status Controller::checkIfEnvironmentData(const SPI_TRANSFER_FORMAT &SpiData)
{


    if((SpiData.header & 0xff) == 'E' && ((SpiData.header >> 8) & 0xff) == 'N')
    {

        gmEnvironmentData = gmSpiRxData;

        gmSpiRxData.clear();

        return Status::ok;

    }
    else
    {
        return Status::error;
    }
}



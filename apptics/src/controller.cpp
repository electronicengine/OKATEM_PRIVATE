#include "controller.h"
#include "globals.h"

extern std::map<const std::string, bool> CheckList;

Controller::Controller()
{


}



Controller::~Controller()
{

}

int Controller::init()
{

    Status status;


    status = gmSpi.init();

    if(status == Status::ok)
    {
        std::thread communication(&Controller::communicationThread, this);
        communication.detach();

        return SUCCESS;

    }
    else
    {
        return FAIL;
    }



}

void Controller::resetStm()
{
    system("sudo echo \"mode 74 0\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");
    system("sudo echo \"dir 74 1\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");
    system("sudo echo \"out 74 0\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");

    system("sudo echo \"mode 200 0\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");
    system("sudo echo \"dir 200 1\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");
    system("sudo echo \"out 200 0\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");

    system("sudo echo \"out 74 1\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");
    system("sudo echo \"out 200 1\" > /sys/devices/platform/1000b000.pinctrl/mt_gpio");

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

    if(Data.servo_motor1_degree != 0)
        gmCalibratedMotorValues.servo_motor1_degree = Data.servo_motor1_degree;

    if(Data.servo_motor2_degree != 0)
        gmCalibratedMotorValues.servo_motor2_degree = Data.servo_motor2_degree;

    gmMutex.unlock();

    return Status::ok;

}



Status Controller::setUpdateData(UPDATE_FILE_FORMAT &Data)
{

    static int percent = 0;
      static int last_percent;


      if(gmIsTransmitted)
      {


          if(gmDesiredPackageSequence >= gmCurrentPackageSequence)
          {
              if(Data.current_sequence_number == 1)
                  resetStm();

             gmMutex.lock();

             gmUpdateFile = Data;

             gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

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

              gmMutex.lock();

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

void Controller::setMotorCalibrationValues(const MOTOR_INFORMATIONS &MotorInformations)
{
    gmCalibratedMotorValues = MotorInformations;
}

Status Controller::checkValidEnvironmentData(ENVIRONMENT_DATA_FORMAT &Data)
{
    if(Data.servo_motor1_degree == 0xff && Data.servo_motor2_degree == 0xff &&
            Data.step_motor1_step == 0xffffffff && Data.step_motor2_step == 0xffffffff)
        return Status::error;
    else
        return Status::ok;

}



ENVIRONMENT_DATA_FORMAT Controller::getStmEnvironment()
{

    ENVIRONMENT_DATA_FORMAT data;

    gmMutex.lock();

    data = gmEnvironmentData;

    gmMutex.unlock();

    return data;
}

int Controller::checkInitilizationNeeded(ENVIRONMENT_DATA_FORMAT &EnvironmentData)
{

    CONTROL_DATA_FORMAT initial_control_data;

    if(EnvironmentData.step_motor1_step == 0xffffffff && EnvironmentData.step_motor2_step == 0xffffffff &&
          EnvironmentData.servo_motor1_degree == 0xff && EnvironmentData.servo_motor1_degree == 0xff) //initiliazation needed
    {

        printAll( "!!!!!!!!!!!  motor positions sent !!!!!!!!!!!!!!!" );

        initial_control_data.y_position = gmCalibratedMotorValues.step_motor1_position;
        initial_control_data.x_position = gmCalibratedMotorValues.step_motor2_position;
        initial_control_data.step_motor1_step = gmCalibratedMotorValues.step_motor1_max_step;
        initial_control_data.step_motor2_step = gmCalibratedMotorValues.step_motor2_max_step;

        initial_control_data.servo_motor1_degree = gmCalibratedMotorValues.servo_motor1_degree;
        std::cout << "calibrated: " << std::to_string(initial_control_data.servo_motor1_degree) << std::endl;


        initial_control_data.servo_motor1_top_degree = gmCalibratedMotorValues.servo_motor1_top_degree;
        initial_control_data.servo_motor1_bottom_degree = gmCalibratedMotorValues.servo_motor1_bottom_degree;

        initial_control_data.servo_motor2_degree = gmCalibratedMotorValues.servo_motor2_degree;
        initial_control_data.servo_motor2_top_degree = gmCalibratedMotorValues.servo_motor2_top_degree;
        initial_control_data.servo_motor2_bottom_degree = gmCalibratedMotorValues.servo_motor2_bottom_degree;

        initial_control_data.setting_enable = 0xff;

        gmSpiTxData = initial_control_data;


        return SUCCESS;

    }
    else
    {
        return FAIL;
    }
}



void Controller::communicationThread()
{

    SPI_TRANSFER_FORMAT spi_data;

    unsigned char *spi_transfer_data;
    int wait_time = 100000;

    Status status;



    printAll("Stm Spi Communication Thread Starting...");

    while(true)
    {

        checkInitilizationNeeded(gmEnvironmentData);

        gmMutex.lock();

        spi_transfer_data = gmSpiTxData;

        gmMutex.unlock();


        printf("%02X-%02X\n", spi_transfer_data[56], spi_transfer_data[57]);


        status = gmSpi.spiTransmiteReceive(spi_transfer_data, SPI_TRANSFER_SIZE);

        if(status == Status::ok)
        {
           spi_data = spi_transfer_data;

            status = checkIfUpdateData(spi_data);

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
                status = checkIfEnvironmentData(spi_data);
                if(status == Status::ok)
                {

                    gmIsReceived = true;
                    gmIsTransmitted = true;
                }
                else
                {

                    gmIsTransmitted = true;
                    gmIsReceived = true;

                }

                gmMutex.lock();
                gmSpiTxData.clear();
                gmMutex.unlock();

            }

        }
        else
        {

            gmIsTransmitted = false;
            gmIsReceived = false;

        }

        delete spi_transfer_data;

        usleep(wait_time);


    }

}



Status Controller::checkIfUpdateData(const SPI_TRANSFER_FORMAT& SpiData)
{

    static UPDATE_FILE_FORMAT backup_update_file;
    UPDATE_FILE_FORMAT file_package_response;

    if((SpiData.header & 0xff) == 'U' && ((SpiData.header >> 8) & 0xff) == 'P')
    {

        file_package_response = SpiData;
        gmDesiredPackageSequence = file_package_response.current_sequence_number;



        if((gmDesiredPackageSequence < gmCurrentPackageSequence))
        {

            printAll(gmDesiredPackageSequence, "<", gmCurrentPackageSequence);

            gmMutex.lock();
            gmSpiTxData = backup_update_file;
            gmMutex.unlock();

            gmCurrentPackageSequence = backup_update_file.current_sequence_number;

            gmIsTransmitted = false;

            return Status::time_out;


        }
        else if((gmDesiredPackageSequence > gmCurrentPackageSequence))
        {

            printAll(gmDesiredPackageSequence, ">", gmCurrentPackageSequence);

            return Status::ok;

        }
        else if(((gmDesiredPackageSequence == gmCurrentPackageSequence)))
        {

            printAll(gmDesiredPackageSequence, "==", gmCurrentPackageSequence);

            backup_update_file = gmUpdateFile;
            gmCurrentPackageSequence = gmUpdateFile.current_sequence_number;

            if(gmCurrentPackageSequence == gmUpdateFile.total_sequence_number)
            {
                printAll("Firmware Updating is done");

                gmMutex.lock();
                gmUpdateFile.clear();
                gmSpiTxData.clear();
                gmMutex.unlock();

                return Status::error;
            }

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

        gmMutex.lock();
        gmEnvironmentData = SpiData;
        gmMutex.unlock();

        return Status::ok;

    }
    else
    {
        return Status::error;
    }
}



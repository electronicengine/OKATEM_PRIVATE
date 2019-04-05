#include "stmdriver.h"
#include "globals.h"

extern std::map<const std::string, bool> CheckList;

StmDriver::StmDriver()
{


}



StmDriver::~StmDriver()
{

}

int StmDriver::init()
{

    Status status;


    status = gmSpi.init();

    if(status == Status::ok)
    {
        std::thread communication(&StmDriver::communicationThread, this);
        communication.detach();

        return SUCCESS;

    }
    else
    {
        return FAIL;
    }



}

void StmDriver::resetStm()
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



Status StmDriver::isReady()
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








Status StmDriver::driveMotorLeft()
{

    gmControlData.step_motor2_direction = FORWARD;
    gmControlData.step_motor2_speed = 36;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status StmDriver::driveMotorRight()
{

    gmControlData.step_motor2_direction = BACKWARD;
    gmControlData.step_motor2_speed = 87;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status StmDriver::driveMotorUp()
{

    gmControlData.step_motor1_direction = FORWARD;
    gmControlData.step_motor1_speed = 45;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;
}



Status StmDriver::driveMotorDown()
{

    gmControlData.step_motor1_direction = BACKWARD;
    gmControlData.step_motor1_speed = 5;

    gmMutex.lock();
    gmSpiTxData = gmControlData;
    gmMutex.unlock();

    return Status::ok;

}



Status StmDriver::setControlData(CONTROL_DATA_FORMAT& ControlData)
{

    gmMutex.lock();

    gmSpiTxData = ControlData;

    if(ControlData.servo_motor1_degree != 0)
        gmCalibratedMotorValues.servo_motor1_degree = ControlData.servo_motor1_degree;

    if(ControlData.servo_motor2_degree != 0)
        gmCalibratedMotorValues.servo_motor2_degree = ControlData.servo_motor2_degree;

    gmMutex.unlock();

    return Status::ok;

}



Status StmDriver::setUpdateData(UPDATE_FILE_FORMAT &Data)
{
    gmMutex.lock();
    gmUpdateFile.push_back(Data);
    gmMutex.unlock();


    if(gmUpdateAvalilable == false)
    {

        printAll("Update starting...");
        while(gmIsTransmitted == false);

        processUpdateData(Data);

        gmUpdateAvalilable = true;
    }


    return Status::ok;
}

void StmDriver::setMotorCalibrationValues(MOTOR_INFORMATIONS &MotorInformations)
{
    gmMutex.lock();
    gmCalibratedMotorValues = MotorInformations;
    gmMutex.unlock();
}

Status StmDriver::checkValidEnvironmentData(ENVIRONMENT_DATA_FORMAT &Data)
{
    if(Data.servo_motor1_degree == 0xff && Data.servo_motor2_degree == 0xff &&
            Data.step_motor1_step == 0xffffffff && Data.step_motor2_step == 0xffffffff)
        return Status::error;
    else
        return Status::ok;

}



ENVIRONMENT_DATA_FORMAT StmDriver::getStmEnvironment()
{

    ENVIRONMENT_DATA_FORMAT data;

    gmMutex.lock();

    data = gmEnvironmentData;

    gmMutex.unlock();

    return data;
}

int StmDriver::checkInitilizationNeeded(ENVIRONMENT_DATA_FORMAT &EnvironmentData)
{

    CONTROL_DATA_FORMAT initial_control_data;

    if(EnvironmentData.step_motor1_step == 0xffffffff && EnvironmentData.step_motor2_step == 0xffffffff &&
          EnvironmentData.servo_motor1_degree == 0xff && EnvironmentData.servo_motor1_degree == 0xff) //initiliazation needed
    {

        printAll( "!!!!!!!!!!!  motor positions sent !!!!!!!!!!!!!!!" );

        initial_control_data.step_motor1_max_step = gmCalibratedMotorValues.step_motor1_max_step;
        initial_control_data.step_motor1_step= gmCalibratedMotorValues.step_motor1_position;

        initial_control_data.step_motor2_max_step = gmCalibratedMotorValues.step_motor2_max_step;
        initial_control_data.step_motor2_step = gmCalibratedMotorValues.step_motor2_position;

        initial_control_data.servo_motor1_degree = gmCalibratedMotorValues.servo_motor1_degree;
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



void StmDriver::communicationThread()
{

    SPI_TRANSFER_FORMAT spi_data;

    unsigned char *spi_transfer_data;
    int wait_time = 100000;

    Status status;

    printAll("Stm Spi Communication Thread Starting...");

    while(true)
    {

        gmMutex.lock();

        checkInitilizationNeeded(gmEnvironmentData);

        spi_transfer_data = gmSpiTxData;

        gmMutex.unlock();

        status = gmSpi.spiTransmiteReceive(spi_transfer_data, SPI_TRANSFER_SIZE);

        if(status == Status::ok)
        {
           spi_data = spi_transfer_data;


           switch (spi_data.header) {
           case SPI_TRANSFER_FORMAT::CONTROL_DATA:

               printAll("comming data is control_data");

               gmMutex.lock();
               gmSpiTxData.clear();
               gmMutex.unlock();
               break;

           case SPI_TRANSFER_FORMAT::ENVIRONMENT_DATA:

               putEnvironmentDataIntoBuffer(spi_data);

               gmMutex.lock();
               gmSpiTxData.clear();
               gmMutex.unlock();

               break;

           case SPI_TRANSFER_FORMAT::UPDATE_FILE:

               processUpdateData(spi_data);

               break;

           default:
               break;
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



void StmDriver::processUpdateData(const SPI_TRANSFER_FORMAT& SpiData)
{

    static uint32_t desired_package_sequence = 0, current_package_sequence = 0;
    UPDATE_FILE_FORMAT file_package_response;
    static UPDATE_FILE_FORMAT file_package;

    file_package_response = SpiData;
    desired_package_sequence = file_package_response.current_sequence_number + 1;

    if(desired_package_sequence == 2)
        resetStm();

    if(desired_package_sequence > current_package_sequence)
    {
        gmMutex.lock();
        file_package = gmUpdateFile.pop_front();
        std::cout << "pull: " << std::to_string(file_package.current_sequence_number);

        gmMutex.unlock();
    }
    else
        std::cout << " delay!!! ";



    std::cout << " desired: " << std::to_string(desired_package_sequence)
              << " current: " << std::to_string(current_package_sequence) << std::endl;

    current_package_sequence = file_package.current_sequence_number;
    gmMutex.lock();
    gmSpiTxData = file_package;
    gmMutex.unlock();


    if(gmUpdateFile.size() == 0)
    {
        printAll("update is done!");
        desired_package_sequence = 0;
        current_package_sequence = 0;

        gmUpdateAvalilable = false;
    }


}



void StmDriver::putEnvironmentDataIntoBuffer(const SPI_TRANSFER_FORMAT &SpiData)
{

    gmMutex.lock();
    gmEnvironmentData = SpiData;
    gmMutex.unlock();

    gmIsReceived = true;
    gmIsTransmitted = true;

}



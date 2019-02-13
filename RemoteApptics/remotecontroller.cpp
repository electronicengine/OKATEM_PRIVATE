#include "mainwindow.h"
#include "remotecontroller.h"



RemoteController::RemoteController(UdpSocket *Socket) : SocketListener(Socket)
{
    gpSocket = Socket;
}



RemoteController::~RemoteController()
{
    gmTerminate = true;

    while(gmTerminated == false);

    gpSocket->terminate();

}

int RemoteController::start(const std::string &IpAddress, int Port)
{
    int ret;

    gmIpAddress = IpAddress;
    gmPort = Port;

    ret = gpSocket->init(IpAddress, Port);

    gpSocket->listen();

    return ret;
}



std::vector<unsigned char> RemoteController::readFile(const std::string &FileName)
{
    FILE *file;
    unsigned char buffer;
    unsigned long fileLen;
    std::vector<unsigned char> container;

    //Open file
    file = fopen(FileName.c_str(), "rb");
    if (!file)
    {
        fprintf(stderr, "Unable to open file");
        fclose(file);

    }
    else
    {
        //Get file length
        fseek(file, 0, SEEK_END);
        fileLen=ftell(file);
        fseek(file, 0, SEEK_SET);


        //Read file contents into buffer
        for(unsigned long i=0; i<fileLen; i++)
        {
            fseek(file, i, SEEK_SET);
            fread(&buffer, 1, 1, file);
            container.push_back(buffer);
        }

        fclose(file);

    }

    return container;
}



void RemoteController::parseAndSendData(std::vector<unsigned char> &Container, const std::string &IpAddress)
{

    int size = Container.size();

    gmIpAddress = IpAddress;

    UPDATE_FILE_FORMAT parsed_file;

    parsed_file.clear();

    int sequence = size / SPI_ENTITY_SIZE;

    if(size % SPI_ENTITY_SIZE != 0)
        sequence++;

    parsed_file.total_sequence_number = sequence;

    gmUpdateFileSequence = sequence;

    for(int i=0; i<sequence; i++)
    {

        if(gmTerminate == true)  // stop thread
            return;

        parsed_file.current_sequence_number = i + 1;

        if(i == sequence - 1)
        {

            int remain = size % SPI_ENTITY_SIZE;

            if(remain == 0)
                remain = SPI_ENTITY_SIZE;


            for(int k=0; k < remain; k++)
                parsed_file.data[k] = Container[k + ( SPI_ENTITY_SIZE * i )];

        }
        else
        {
            for(int k=0; k< SPI_ENTITY_SIZE; k++)
                parsed_file.data[k] = Container[k + ( SPI_ENTITY_SIZE * i )];

        }



        gpSocket->sendData((SPI_TRANSFER_FORMAT) parsed_file);

        std::cout << parsed_file.current_sequence_number << "/" << parsed_file.total_sequence_number << " Transmitted \r" << std::endl;

        usleep(50000);
    }

}



void RemoteController::servo1SetValue(int Value)
{

    gmTxData.clear();

    gmTxData.servo_motor1_degree = Value;

    gpSocket->sendData((SPI_TRANSFER_FORMAT) gmTxData);
    printf("Servo1 setting value %d\r\n", gmTxData.servo_motor1_degree );

}



void RemoteController::servo2SetValue(int Value)
{

    gmTxData.clear();

    gmTxData.servo_motor2_degree = Value;


    gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    printf("Servo2 setting value %d\r\n", gmTxData.servo_motor2_degree );

}

void RemoteController::stop()
{
    gmTxData.clear();
}





void RemoteController::turnLeft()
{

    int ret;

    gmTxData.step_motor2_direction = FORWARD;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmTxData.step_motor1_speed = gmSpeed;
    gmTxData.step_motor2_speed = gmSpeed;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);
    else
        printf("LEFT %d\r\n", gmTxData.step_motor1_speed);

}



void RemoteController::turnRight()
{

    int ret;

    gmTxData.step_motor2_direction = BACKWARD;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.step_motor1_speed = gmSpeed;
    gmTxData.step_motor2_speed = gmSpeed;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);
    else
        printf("RIGHT %d\r\n", gmTxData.step_motor1_speed);

}



void RemoteController::turnUp()
{

    int ret;

    gmTxData.step_motor1_direction = FORWARD;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmTxData.step_motor1_speed = gmSpeed;
    gmTxData.step_motor2_speed = gmSpeed;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);
    else
        printf("UP %d\r\n", gmTxData.step_motor1_speed);

}


void RemoteController::turnDown()
{

    int ret;

    gmTxData.step_motor1_direction = BACKWARD;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmTxData.step_motor1_speed = gmSpeed;
    gmTxData.step_motor2_speed = gmSpeed;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);
    else
        printf("DOWN %d\r\n", gmTxData.step_motor1_speed);

}

void RemoteController::setCalibrationValues(const CONTROL_DATA_FORMAT &CalibrationValues)
{
    int ret;

    gmTxData.clear();

    gmTxData = CalibrationValues;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);
    else
        printf("CALIB %d\r\n", gmTxData.step_motor1_speed);
}



void RemoteController::increaseSpeed()
{
    gmSpeed++;

    if(gmSpeed > 20 )
        gmSpeed = 20;

    printf("Speed: %d\r\n", MAX_INVERSE_SPEED_VALUE - gmSpeed);

}



void RemoteController::decreaseSpeed()
{

    gmSpeed--;

    if(gmSpeed < 1 )
        gmSpeed = 1;

    printf("Speed: %d\r\n", MAX_INVERSE_SPEED_VALUE - gmSpeed);


}



void RemoteController::setSpeed(int value)
{
    if(value == 20)
        value = 19;

    if(value == 0)
        value = 1;

    gmSpeed = MAX_INVERSE_SPEED_VALUE - value;
}



void RemoteController::updateFirmware(const std::string &FileName)
{

    std::cout << "update firmware" << std::endl;

    std::thread update(&RemoteController::updateThread, this, FileName);
    update.detach();


}



int RemoteController::getFsoInformations(CONTROL_DATA_FORMAT &ControlData, ENVIRONMENT_DATA_FORMAT &EnvironmentData, SFP_DATA_FORMAT &SfpData)
{

    UDP_DATA_FORMAT request_package;

    int timeout_counter = 0;
    int ret;


    if(gmUploadingStart != true)
    {
        request_package.header = ('I' | ('N' << 8));


        ret = gpSocket->sendData(request_package);

        if(ret != SUCCESS)
        {
            std::cout << "Information Data Request can not be sent" << std::endl;
            return FAIL;
        }

        while(gmInformationData.is_available == false)
        {
            std::cout << "information data waiting" << std::endl;
            timeout_counter++;

            if(timeout_counter >= 200)
                return FAIL;

            usleep(10000);
        }

        gmMutex.lock();
        ControlData = gmInformationData.control_data;
        EnvironmentData = gmInformationData.environment_data;
        SfpData = gmInformationData.sfp_data;
        gmMutex.unlock();

        return SUCCESS;
    }
    else
    {
        return FAIL;
    }



}

int RemoteController::resetUpdatePercentage()
{
    gmMutex.lock();
    gpSocket->setFeedBackCounter(0);
    gmUpdatePercentage = 0;
    gmMutex.unlock();

    return SUCCESS;
}

int RemoteController::gotoPositions(uint32_t XPosition, uint32_t YPosition)
{

    int ret;
    ENVIRONMENT_DATA_FORMAT information;

    do
    {

        gmTxData.clear();

        gmTxData.step_motor1_speed = MAX_STEPMOTOR_SPEED;
        gmTxData.step_motor2_speed = MAX_STEPMOTOR_SPEED;

        gmTxData.x_position = XPosition;
        gmTxData.y_position = YPosition;

        ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
        if(ret != SUCCESS)
            printf("can not be sent!\r\n");

        gmMutex.lock();
        information = gmInformationData.environment_data;
        gmMutex.unlock();

        usleep(50000);

    }while(information.step_motor1_step != YPosition || information.step_motor2_step != XPosition);

    return ret;
}

int RemoteController::turntoDirection(uint32_t DirectionCommand, uint32_t Duration)
{

    int duration = 0;

    do{
        switch (DirectionCommand)
        {
            case Up:
                stop();
                turnUp();
                break;
            case Down:
                stop();
                turnDown();
                break;
            case Left:
                stop();
                turnLeft();
                break;
            case Right:
                stop();
                turnRight();
                break;
            case UpLeft:
                turnUp();
                turnLeft();
                break;
            case UpRight:
                turnUp();
                turnRight();
                break;
            case DownLeft:
                turnDown();
                turnLeft();
                break;
            case DownRight:
                turnDown();
                turnRight();
                break;

            default:
                break;
        }

        usleep(50000);
        duration += 50;

    }while(duration <= (int)Duration);

    return SUCCESS;

}



int RemoteController::getUpdatePercentage()
{
    int percent;

    gmMutex.lock();
    percent = gmUpdatePercentage;
    gmMutex.unlock();

    return percent;
}

void RemoteController::socketDataCheckCall()
{

    gmMutex.lock();

    gmInformationData = gpSocket->getInformationData();

    gmUpdatePercentage = ((float)((float)(gpSocket->getFeedBackCounter()) / gmUpdateFileSequence)) * 100;

    gmMutex.unlock();

}

int RemoteController::terminate()
{
    gmTerminate = true;

    while(gmTerminated == false);

    gpSocket->terminate();

    return SUCCESS;
}


void RemoteController::updateThread(const std::string &FileName)
{

    std::vector<unsigned char> data;

    gmTerminated = false;

    data = readFile(FileName);
    parseAndSendData(data, gmIpAddress);

    gmTerminated = true;
}



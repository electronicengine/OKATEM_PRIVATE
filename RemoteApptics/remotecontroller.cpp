#include "mainwindow.h"
#include "remotecontroller.h"
#include "displaypanel.h"


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

int RemoteController::start(const std::string &IpAddress, int Port, DisplayPanel *DisplayWindow)
{
    int ret;

    gmIpAddress = IpAddress;
    gmPort = Port;
    gpDisplayPanel = DisplayWindow;

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

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}



void RemoteController::servo2SetValue(int Value)
{

    gmTxData.clear();

    gmTxData.servo_motor2_degree = Value;


    gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    printf("Servo2 setting value %d\r\n", gmTxData.servo_motor2_degree );

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}

void RemoteController::stop()
{    
    gmTxData.setting_enable = 0;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.step_motor1_direction = 0;
    gmTxData.step_motor2_direction = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmTxData.calibrate_sensor = 0;

    gmTxData.step_motor1_step = 0;
    gmTxData.step_motor2_step = 0;

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}





void RemoteController::turnLeft()
{

    int ret;

    gmTxData.step_motor2_direction = FORWARD;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}



void RemoteController::turnRight()
{

    int ret;

    gmTxData.step_motor2_direction = BACKWARD;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}



void RemoteController::turnUp()
{

    int ret;

    gmTxData.step_motor1_direction = FORWARD;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}


void RemoteController::turnDown()
{

    int ret;

    gmTxData.step_motor1_direction = BACKWARD;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}

void RemoteController::setCalibrationValues(const CONTROL_DATA_FORMAT &CalibrationValues)
{
    int ret;

    gmTxData.clear();

    gmTxData = CalibrationValues;

    ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
    if(ret != SUCCESS)
        printf("can not be sent %d\r\n", gmTxData.step_motor1_speed);

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();
}



void RemoteController::setStep1Speed(int value, int Max)
{
    if(value > MAX_STEPMOTOR_SPEED)
        value = MAX_STEPMOTOR_SPEED;


    gmTxData.step_motor1_speed = Max - value;

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}

void RemoteController::setStep2Speed(int value, int Max)
{
    if(value > MAX_STEPMOTOR_SPEED)
        value = MAX_STEPMOTOR_SPEED;

    gmTxData.step_motor2_speed = Max - value;

    gmControlSignalMutex.lock();
    gmControlSignal = gmTxData;
    gmControlSignalMutex.unlock();

}



void RemoteController::updateFirmware(const std::string &FileName)
{

    std::cout << "update firmware" << std::endl;

    std::thread update(&RemoteController::updateThread, this, FileName);
    update.detach();


}



int RemoteController::resetUpdatePercentage()
{
    gmMutex.lock();
    gpSocket->setFeedBackCounter(0);
    gmUpdatePercentage = 0;
    gmMutex.unlock();

    return SUCCESS;
}

int RemoteController::sendRFSwitchRequest()
{
    int ret;
    UDP_DATA_FORMAT request;

    request.header = UDP_DATA_FORMAT::RF_SWITCH_REQUEST;

    ret = gpSocket->sendData(request);

    return ret;
}

int RemoteController::sendLaserSwitchRequest()
{
    int ret;
    UDP_DATA_FORMAT request;

    request.header = UDP_DATA_FORMAT::LASER_SWITCH_REQUEST;

    std::cout << "sendLaserSwitchRequestIn!!!!!!" << std::endl;
    ret = gpSocket->sendData(request);

    return ret;
}

int RemoteController::gotoPositions(uint32_t XPosition, uint32_t YPosition)
{

    int ret;
    ENVIRONMENT_DATA_FORMAT information;

    do
    {

        stop();

        gmTxData.x_position = XPosition;
        gmTxData.y_position = YPosition;

        ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
        if(ret != SUCCESS)
            printf("can not be sent!\r\n");

        gmMutex.lock();
        information = gmInformationData.environment_data;
        gmMutex.unlock();

        usleep(50000);

        gmControlSignalMutex.lock();
        gmControlSignal = gmTxData;
        gmControlSignalMutex.unlock();

    }while(information.step_motor1_step != YPosition || information.step_motor2_step != XPosition);


    return ret;
}

int RemoteController::turntoDirection(uint32_t DirectionCommand, uint32_t Duration)
{

    int ret;
    int duration = 0;

    gmTxData.x_position = 0;
    gmTxData.y_position = 0;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    do{
        switch (DirectionCommand)
        {
            case Up:        
                gmTxData.step_motor1_direction = FORWARD;
                gmTxData.step_motor2_direction = STOP;

                break;
            case Down:
                gmTxData.step_motor1_direction = BACKWARD;
                gmTxData.step_motor2_direction = STOP;

                break;
            case Left:
                gmTxData.step_motor1_direction = STOP;
                gmTxData.step_motor2_direction = FORWARD;

                break;
            case Right:
                gmTxData.step_motor1_direction = STOP;
                gmTxData.step_motor2_direction = BACKWARD;

                break;
            case UpLeft:
                gmTxData.step_motor1_direction = FORWARD;
                gmTxData.step_motor2_direction = FORWARD;

                break;
            case UpRight:
                gmTxData.step_motor1_direction = FORWARD;
                gmTxData.step_motor2_direction = BACKWARD;

                break;
            case DownLeft:
                gmTxData.step_motor1_direction = BACKWARD;
                gmTxData.step_motor2_direction = FORWARD;

                break;
            case DownRight:
                gmTxData.step_motor1_direction = BACKWARD;
                gmTxData.step_motor2_direction = BACKWARD;
                break;

            default:
                break;
        }

        ret = gpSocket->sendData((SPI_TRANSFER_FORMAT)gmTxData);
        if(ret != SUCCESS)
            printf("direction can not be sent.\r\n");

        usleep(50000);
        duration += 50;

    }while(duration <= (int)Duration);

    return SUCCESS;

}

CONTROL_DATA_FORMAT RemoteController::getControlData()
{
    CONTROL_DATA_FORMAT control_data;

    gmMutex.lock();
    control_data = gmControlSignal;
    gmMutex.unlock();

    return control_data;
}



int RemoteController::sendCameraSettingsRequest(const CAMERA_SETTINGS_FORMAT &CameraSettings)
{
    return gpSocket->sendData(CameraSettings);
}

int RemoteController::sendInformationRequest()
{
    UDP_DATA_FORMAT request_package;

    int ret;

    request_package.header = UDP_DATA_FORMAT::INFORMATION_DATA;

    ret = gpSocket->sendData(request_package);

    if(ret != SUCCESS)
    {
        std::cout << "Information Data Request can not be sent" << std::endl;
        return FAIL;
    }

    return SUCCESS;

}




void RemoteController::socketDataCheckCall()
{

    INFORMATION_DATA_FORMAT information_data;
    int update_counter;

    information_data = gpSocket->getInformationData();
    update_counter = gpSocket->getFeedBackCounter();


    gmMutex.lock();
    gmInformationData = information_data;
    gmUpdatePercentage = ((float)((float)(update_counter) / gmUpdateFileSequence)) * 100;
    gmMutex.unlock();


    if(gpSocket->isEthernetConnected() == true)
    {
        if(information_data.is_available == true)
            gpDisplayPanel->panelInformationCallBack(information_data);
        else if(update_counter > 0)
            gpDisplayPanel->upgradingFirmworkCallBack((((float)((float)(update_counter) / gmUpdateFileSequence)) * 100));

    }
    else
    {
        gpDisplayPanel->ethernetConnectionLostCallBack();
    }





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



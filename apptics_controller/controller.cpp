#include "controller.h"


Controller::Controller(const std::string &IpAddress, int Port)
{


    gmIpAddress = IpAddress;
    gmPort = Port;

    std::cout << "Enter Servo Motor1 Position " << std::endl;
    std::cin >> gmSpeed;

    std::cout << "Enter Servo Motor2 Position " << std::endl;
    std::cin >> gmServoMotor2Degree;


    gmSocket.openPort(Port, LISTENING_MODE);

}


std::vector<unsigned char> Controller::readFile()
{
    FILE *file;
    unsigned char buffer;
    unsigned long fileLen;
    std::vector<unsigned char> container;

    //Open file
    file = fopen("stm32f746_rtos.bin", "rb");
    if (!file)
    {
        fprintf(stderr, "Unable to open file");

    }
    else
    {
        //Get file length
        fseek(file, 0, SEEK_END);
        fileLen=ftell(file);
        fseek(file, 0, SEEK_SET);


        //Read file contents into buffer
        for(int i=0; i<fileLen; i++)
        {
            fseek(file, i, SEEK_SET);
            fread(&buffer, 1, 1, file);
            container.push_back(buffer);
        }

        fclose(file);

    }

    return container;
}


void Controller::parseAndSendData(std::vector<unsigned char> &Container, const std::string &IpAddress)
{

    int size = Container.size();



    UPDATE_FILE_FORMAT parsed_file;

    parsed_file.clear();

    int sequence = size / SPI_ENTITY_SIZE;

    if(size % SPI_ENTITY_SIZE != 0)
        sequence++;

    parsed_file.total_sequence_number = sequence;

    for(int i=0; i<sequence; i++)
    {

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



        gmSocket.sendData((SPI_TRANSFER_FORMAT)parsed_file, gmIpAddress);

        std::cout << parsed_file.current_sequence_number << "/" << parsed_file.total_sequence_number << " Transmitted \r" << std::endl;


        usleep(50000);
    }

}

void Controller::run(const std::string &IpAddress, int Port)
{


}



void Controller::servo1Forward()
{

    gmTxData.clear();

    gmTxData.servo_motor1_degree = ++gmServoMotor1Degree;
    gmTxData.servo_motor2_degree = 0;

    if(gmServoMotor1Degree >= 150)
        gmServoMotor1Degree = 150;

    if(gmServoMotor1Degree < 64)
        gmServoMotor1Degree = 64;

    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("Servo1 Forward %d\r\n", gmServoMotor1Degree);

}

void Controller::servo2Forward()
{

    gmTxData.clear();
    gmTxData.servo_motor2_degree = ++gmServoMotor2Degree;
    gmTxData.servo_motor1_degree = 0;

    if(gmServoMotor2Degree >= 150)
        gmServoMotor2Degree = 150;



    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("Servo2 Forward %d\r\n",gmServoMotor2Degree);

}

void Controller::servo1Backward()
{


    gmTxData.clear();
    gmTxData.servo_motor1_degree = --gmServoMotor1Degree;
    gmTxData.servo_motor2_degree = 0;

    if(gmServoMotor1Degree <= 0)
        gmServoMotor1Degree = 0;


    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("Servo1 Forward %d\r\n",gmServoMotor1Degree);

}

void Controller::servo2Backward()
{
    gmTxData.clear();
    gmTxData.servo_motor2_degree = --gmServoMotor2Degree;
    gmTxData.servo_motor1_degree = 0;

    if(gmServoMotor2Degree <= 0)
        gmServoMotor2Degree = 0;


    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("Servo2 Down %d\r\n",gmServoMotor2Degree);

}

void Controller::turnLeft()
{

    gmTxData.clear();
    gmTxData.x_position = 365;
    gmTxData.step_motor2_direction = 1;
    gmTxData.step_motor2_speed = gmSpeed;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("LEFT\r\n");

}

void Controller::turnRight()
{

    gmTxData.clear();
    gmTxData.x_position = 365;
    gmTxData.step_motor2_direction = 2;
    gmTxData.step_motor2_speed = gmSpeed;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("RIGHT\r\n");

}

void Controller::turnUp()
{

    gmTxData.clear();
    gmTxData.x_position = 365;
    gmTxData.step_motor1_direction = 1;
    gmTxData.step_motor1_speed = gmSpeed;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("UP\r\n");

}

void Controller::turnDown()
{

    gmTxData.clear();
    gmTxData.x_position = 365;
    gmTxData.step_motor1_direction = 2;
    gmTxData.step_motor1_speed = gmSpeed;

    gmTxData.servo_motor1_degree = 0;
    gmTxData.servo_motor2_degree = 0;

    gmSocket.sendData((SPI_TRANSFER_FORMAT)gmTxData, gmIpAddress);
    printf("DOWN\r\n");

}

void Controller::increaseSpeed()
{
    gmSpeed++;

    if(gmSpeed > 20 )
        gmSpeed = 20;

    printf("Speed: %d\r\n", MAX_SPEED - gmSpeed);

}

void Controller::decreaseSpeed()
{

    gmSpeed--;

    if(gmSpeed < 1 )
        gmSpeed = 1;

    printf("Speed: %d\r\n", MAX_SPEED - gmSpeed);


}


void Controller::updateFirmware()
{

    std::vector<unsigned char> data;

    data = readFile();
    parseAndSendData(data, gmIpAddress);
    data.clear();
}

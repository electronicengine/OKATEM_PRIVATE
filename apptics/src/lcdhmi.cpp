#include "lcdhmi.h"


extern std::map<std::string, bool> CheckList;

LcdHMI::LcdHMI()
{

}

LcdHMI::~LcdHMI()
{
    delete gmSerial;
}

CONTROL_DATA_FORMAT LcdHMI::getHCMControlData()
{

    CONTROL_DATA_FORMAT data;

     if(gmDataComing == true)
     {
         gmMutex.lock();


        data = gmControlData;
        data = true;
        gmMutex.unlock();

        return data;
     }
     else
     {

         data = false;
         return data;
     }

}

Status LcdHMI::setInitialMotorPositions(CONTROL_DATA_FORMAT &SavedData)
{

    servo_motor1_angle = SavedData.servo_motor1_degree;
    servo_motor2_angle = SavedData.servo_motor2_degree;

}

Status LcdHMI::setHCMData(SFP_DATA_FORMAT &SfpData, ENVIRONMENT_DATA_FORMAT &EnvironmentData)
{

    gmMutex.lock();

    gmSfpData = SfpData;
    gmStmEnvironmentData = EnvironmentData;

    gmMutex.unlock();

    return Status::ok;

}

void LcdHMI::callSensorPage(std::vector<unsigned char> &Data)
{
    if(Data[1] == CALLBACKTOKEN || Data[2] == PAGE_CHANGED)
    {
        gmMutex.lock();
        sendEnvironmentInfo();

        gmDataComing = false;
        gmControlData.calibrate_sensor = 0;

        gmMutex.unlock();
    }
    if(Data[1] == BUTTON_PRESSED)
    {
        if(Data[2] == CALIBRATE_BUTTON_ID)
        {
            gmMutex.lock();

            printAll("Sensor Calibrate");

            gmDataComing = true;

            gmControlData.calibrate_sensor = 1;

            gmMutex.unlock();
        }
    }else if(Data[1] == BUTTON_UNPRESSED)
    {

        gmDataComing = false;
        gmMutex.lock();
        gmControlData.calibrate_sensor = 0;
        gmMutex.unlock();

    }
    else
    {

    }

}

void LcdHMI::callManualPage(std::vector<unsigned char> &Data)
{

    int speed;


    gmMutex.lock();

    if(Data[1] == BUTTON_PRESSED)
    {

        gmDataComing = true;
        if(Data[2] == UP_BUTTON_ID)
        {
            printAll("up botton");
            gmControlData.step_motor1_direction = FORWARD;


            gmControlData.servo_motor1_degree = 0;
            gmControlData.servo_motor2_degree = 0;

        }

        if(Data[2] == DOWN_BUTTON_ID)
        {
            printAll("down");
            gmControlData.step_motor1_direction = BACKWARD;


            gmControlData.servo_motor1_degree = 0;
            gmControlData.servo_motor2_degree = 0;
        }

        if(Data[2] == RIGHT_BUTTON_ID)
        {
            printAll("right");
            gmControlData.step_motor2_direction = FORWARD;

            gmControlData.servo_motor1_degree = 0;
            gmControlData.servo_motor2_degree = 0;
        }

        if(Data[2] == LEFT_BUTTON_ID)
        {
            printAll("left");
            gmControlData.step_motor2_direction = BACKWARD;


            gmControlData.servo_motor1_degree = 0;
            gmControlData.servo_motor2_degree = 0;
        }

//        speed = 0;
        printf("%d\r\n", Data[6]);

        if(Data[6] == 0)
            speed = 20;
        else if(Data[6] == 100)
            speed = 0;
        else
        {
            speed = 20 - ((int)((double)Data[6] / 20) * 5);
        }

        gmControlData.step_motor1_speed = 1;
        gmControlData.step_motor2_speed = 1;

    }
    else if(Data[1] == BUTTON_UNPRESSED)
    {

        printAll("unpressed");
        gmDataComing = false;
        gmControlData.clear();

    }

    gmMutex.unlock();

}



void LcdHMI::callAutoPage(std::vector<unsigned char> &Data)
{

   static bool enable = true;

    if(Data[1] == BUTTON_PRESSED)
    {

        if(Data[2] == AUTOMODE_START && enable == true)
        {
            printAll("AutoMode Start button");

            gmAutoModeEnable = true;
            enable = false;
            std::thread auto_mode(&LcdHMI::autoMode, this);
            auto_mode.detach();

        }

        if(Data[2] == AUTOMODE_STOP)
        {
            gmAutoModeEnable = false;
            enable = true;
        }
        if(Data[2] == AUTOMODE_PAUSE)
        {
            gmAutoModeEnable = false;
            enable = true;
        }



    }

}



void LcdHMI::callCameraPage(std::vector<unsigned char> &Data)
{

   gmMutex.lock();

    if(Data[1] == BUTTON_PRESSED)
    {

        gmDataComing = true;

        if(Data[2] == CAMERA1_UP_BUTTON_ID)
        {

            if(servo_motor1_angle<= 150)
                servo_motor1_angle += Data[6];

            if(servo_motor1_angle >= 150)
                servo_motor1_angle = 150;

            if(servo_motor1_angle <= 0)
                servo_motor1_angle = 0;

            gmControlData.servo_motor1_degree = servo_motor1_angle;

            gmSerial->writeData("t1.txt=\"", std::to_string(servo_motor1_angle), " Deg\";");

            printf("Camera1 Up %d\r\n", servo_motor1_angle);
        }

        if(Data[2] == CAMERA1_DOWN_BUTTON_ID)
        {
            if(servo_motor1_angle >= 0)
                servo_motor1_angle -= Data[6];

            if(servo_motor1_angle >= 150)
                servo_motor1_angle = 150;

            if(servo_motor1_angle <= 0)
                servo_motor1_angle = 0;

            gmControlData.servo_motor1_degree = servo_motor1_angle;

            gmSerial->writeData("t1.txt=\"", std::to_string(servo_motor1_angle), " Deg\";");

            printf("Camera1 Down %d\r\n", servo_motor1_angle);
        }

        if(Data[2] == CAMERA2_UP_BUTTON_ID)
        {

            if(servo_motor2_angle <= 150)
                servo_motor2_angle += Data[6];

            if(servo_motor2_angle >= 150)
                servo_motor2_angle = 150;

            if(servo_motor2_angle <= 0)
                servo_motor2_angle = 0;

            gmControlData.servo_motor2_degree = servo_motor2_angle;

            gmSerial->writeData("t2.txt=\"", std::to_string(servo_motor2_angle), " Deg\";");

            printf("Camera2 Up %d\r\n", servo_motor2_angle);
        }

        if(Data[2] == CAMERA2_DOWN_BUTTON_ID)
        {

            if(servo_motor2_angle >= 0)
                servo_motor2_angle -= Data[6];

            if(servo_motor2_angle >= 150)
                servo_motor2_angle = 150;

            if(servo_motor2_angle <= 0)
                servo_motor2_angle = 0;

            gmControlData.servo_motor2_degree = servo_motor2_angle;

            gmSerial->writeData("t2.txt=\"", std::to_string(servo_motor2_angle), " Deg\";");

            printf("Camera2 Down %d\r\n", servo_motor2_angle);
        }

    }

    if(Data[1] == BUTTON_UNPRESSED)
    {
        gmDataComing = false;

    }

    gmMutex.unlock();


}



int LcdHMI::init()
{

    Status status;

    gmSerial = new SerialCom("B115200", "/dev/ttyUSB0");

    status = gmSerial->Init();

    if(status == Status::ok)
    {
        printAll("LcdHMI Serial Port Succesfully Openned");

        servo_motor1_angle = 50;
        servo_motor2_angle = 50;

        std::thread listen(&LcdHMI::listenHMI, this);
        listen.detach();

        return SUCCESS;
    }
    else
    {
        return FAIL;
    }


}



void LcdHMI::listenHMI()
{




    Status status;
    std::vector<unsigned char> hcm_data;



    printAll("listenHMI");

    while(1)
    {
        status = gmSerial->readData(hcm_data, HEADER, FOOTER);

        if(status == Status::ok)
        {

            if(hcm_data.size() > 0)
            {
                gmCurrentPage = hcm_data.data()[0];

                if(gmCurrentPage == MANUAL_PAGE_ID)
                {
                    printAll("HMI Main Page");

                    callManualPage(hcm_data);

                }
                if(gmCurrentPage == SENSORS_PAGE_ID)
                {

                   callSensorPage(hcm_data);
                }
                if(gmCurrentPage == AUTO_PAGE_ID)
                {
                   callAutoPage(hcm_data);
                }
                if(gmCurrentPage == CAMERA_PAGE_ID)
                {
                    callCameraPage(hcm_data);
                }

                hcm_data.clear();
            }

        }

    }

}



void LcdHMI::autoMode()
{

    sleep(1);

//    gmAutoModeEnable = true;

    while(1)
    {

        gmDataComing = true;

        gmControlData.step_motor1_speed = 1;
        gmControlData.step_motor2_speed = 1;


        printAll("up");
        gmControlData.step_motor2_direction = FORWARD;
        gmControlData.step_motor1_direction = FORWARD;

        sleep(10);

        gmDataComing = false;

        if(gmAutoModeEnable == false)
            break;


        sleep(1);

        gmDataComing = true;

        gmControlData.step_motor1_speed = 1;
        gmControlData.step_motor2_speed = 1;

        printAll("down");
        gmControlData.step_motor2_direction = BACKWARD;
        gmControlData.step_motor1_direction = BACKWARD;

        sleep(10);

        gmDataComing = false;

        if(gmAutoModeEnable == false)
            break;

        sleep(1);


        gmDataComing = true;

        gmControlData.step_motor1_speed = 1;
        gmControlData.step_motor2_speed = 1;

        printAll("down");
        gmControlData.step_motor2_direction = BACKWARD;
        gmControlData.step_motor1_direction = FORWARD;

        sleep(10);

        gmDataComing = false;

        if(gmAutoModeEnable == false)
            break;

        sleep(1);



        gmDataComing = true;

        gmControlData.step_motor1_speed = 1;
        gmControlData.step_motor2_speed = 1;

        printAll("down");
        gmControlData.step_motor2_direction = FORWARD;
        gmControlData.step_motor1_direction = BACKWARD;

        sleep(10);

        gmDataComing = false;

        if(gmAutoModeEnable == false)
            break;

        sleep(1);



    }

    gmDataComing = false;

}



Status LcdHMI::sendEnvironmentInfo()
{

    std::string wheather;
    std::string sfp_status;

    if(gmSfpData.status == 1)
        sfp_status = "Connected";
    else
        sfp_status = "Unconnected";

    if(gmStmEnvironmentData.sensor_data.wheather_condition == 1)
        wheather = "Sunny";
    else if(gmStmEnvironmentData.sensor_data.wheather_condition == 2)
        wheather = "Cloudy";
    else if(gmStmEnvironmentData.sensor_data.wheather_condition == 3)
        wheather = "Rainy";
    else
        wheather = "Undetermined";

    gmSerial->writeData("stat.txt=\"Stat:", sfp_status, " \";");
    usleep(100);
    gmSerial->writeData("temp.txt=\"Temp: ", gmStmEnvironmentData.sensor_data.temperature," C\";");
    usleep(100);
    gmSerial->writeData("press.txt=\"Press: ", gmStmEnvironmentData.sensor_data.pressure," hm\";");
    usleep(100);
    gmSerial->writeData("comp.txt=\"Comp: ", gmStmEnvironmentData.sensor_data.compass_degree," d\";");
    usleep(100);
    gmSerial->writeData("alti.txt=\"Alttude: ", gmStmEnvironmentData.sensor_data.altitude," m\";");
    usleep(100);
    gmSerial->writeData("wheat.txt=\"Wheather: ", wheather," \";");

}





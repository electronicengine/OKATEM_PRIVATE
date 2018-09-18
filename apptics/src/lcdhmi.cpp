#include "lcdhmi.h"



LcdHMI::LcdHMI()
{
    initHCM();
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

Status LcdHMI::setHCMData(SFP_DATA_FORMAT &SfpData, ENVIRONMENT_DATA_FORMAT &EnvironmentData)
{

}

void LcdHMI::writeControlData(std::vector<unsigned char> &Data)
{



    for(int i=0; i<Data.size(); i++)
        printf("%02x-", Data[i]);

    printf("\n");


    if(Data[1] == BUTTON_PRESSED)
    {


        gmDataComing = true;
        if(Data[2] == UP_BUTTON_ID)
        {
            printAll("up botton");
            gmControlData.step_motor1_direction = FORWARD;
        }

        if(Data[2] == DOWN_BUTTON_ID)
        {
            gmControlData.step_motor1_direction = BACKWARD;
        }

        if(Data[2] == RIGHT_BUTTON_ID)
        {
            gmControlData.step_motor2_direction = FORWARD;
        }

        if(Data[2] == LEFT_BUTTON_ID)
        {
            gmControlData.step_motor2_direction = BACKWARD;
        }


        gmControlData.step_motor1_speed = (Data[3] % 20);
        gmControlData.step_motor2_speed = (Data[3] % 20);
        gmControlData.step_motor3_speed = (Data[3] % 20);
        gmControlData.step_motor4_speed = (Data[3] % 20);

    }
    else if(Data[1] == BUTTON_UNPRESSED)
    {

        printAll("unpressed");
        gmDataComing = false;
        gmControlData.clear();

    }



}

void LcdHMI::initHCM()
{
    std::thread listen(&LcdHMI::listenHMI, this);
    listen.detach();
}

void LcdHMI::listenHMI()
{

    SerialCom Serial("B9600", "/dev/ttyUSB0");


    Status status;
    std::vector<unsigned char> hcm_data;
    const unsigned char header = 0x50;
    const unsigned char footer = 0x51;


    printAll("listenHMI");

    while(1)
    {
        status = Serial.readData(hcm_data, header, footer);

        if(status == Status::ok)
        {



            gmCurrentPage = hcm_data[0];

            if(gmCurrentPage == MANUAL_PAGE_ID)
            {


                gmMutex.lock();
                writeControlData(hcm_data);
                gmMutex.unlock();
            }




            hcm_data.clear();


        }

    }


}





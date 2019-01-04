#include "motorops.h"
#include "main.h"
#include "motor.h"
#include "tim.h"
#include "flash.h"


volatile int speed = 0;


void motorOps(void const * argument)
{

    //  (1/(108.000.000/(psc+1))*period) -> timer width

    osStatus status;

    mprintf("motorOps\r\n");

//    loadMotorPositions();

    while(1)
    {

        driveStepMotors();

        driveServoMotors();

//        saveMotorPositions();

        xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

        EnvironmentData->step_motor1_step = motor1.step_number;
        EnvironmentData->step_motor2_step = motor2.step_number;
        EnvironmentData->servo_motor1_degree = servo1.angle;
        EnvironmentData->servo_motor2_degree = servo2.angle;

        xSemaphoreGive(spiMutexHandle);

        osDelay(2 + speed);

    }
}

void driveStepMotors()
{
    int step_motor1_break;
    int step_motor2_break;

    step_motor1_break = HAL_GPIO_ReadPin(STEP1_BREAK_GPIO_Port, STEP1_BREAK_Pin);
    step_motor2_break = HAL_GPIO_ReadPin(STEP2_BREAK_GPIO_Port, STEP2_BREAK_Pin);

//    if(step_motor1_break)
//    {
        if(motor1.direction == FORWARD)
        {
            motor1Drive(FORWARD);
            speed = motor1.speed;
            motor1.step_number++;

        }
        else if(motor1.direction == BACKWARD)
        {
            motor1Drive(BACKWARD);
            speed = motor1.speed;

            if(motor1.step_number != 0)
                motor1.step_number--;

        }
        else
        {
            motor1Drive(STOP);
        }
//    }



    if(step_motor2_break)
    {
        if(motor2.direction == FORWARD )
        {
            motor2Drive(FORWARD);
            speed = motor1.speed;
            motor2.step_number++;

        }
        else if(motor2.direction == BACKWARD)
        {
            motor2Drive(BACKWARD);
            speed = motor1.speed;

            if(motor2.step_number != 0)
                motor2.step_number--;
        }
        else
        {
            motor2Drive(STOP);
        }
    }




}

void driveServoMotors()
{
    static int counter1 = 0;
    static int counter2 = 0;

    static int servo2_degree = 0;
    static int servo1_degree = 0;

    if(servo2.angle != 0)
    {
       HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

       servo2_degree = servo2.angle;

       counter2 = 0;
       speed = 1;
    }

    if(counter2 <= 100)
    {
      counter2 ++;
      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, (servo2_degree)*((double)(215-60)/150) + 60); // (servo1_degree)*((double)(215-60)/150) + 60) and for own servo
    }
    else
    {
       HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    }

    if(servo1.angle != 0)
    {
       HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

       servo1_degree = servo1.angle;

       counter1 = 0;
       speed = 1;
    }


    if(counter1 <= 100)
    {
      counter1 ++;
      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (servo1_degree)*((double)(215-60)/150) + 60) ; // (int)((double)(servo1_degree)*((double)(200-100)/150) + 100));and for own servo
    }
    else
    {
       HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    }
}



void loadMotorPositions()
{

     uint8_t *flash_data;

     int index = 0;

     flash_data = readFlash(SECTOR6_ADDRESS);

     motor1.step_number = flash_data[index++];
     motor1.step_number |= flash_data[index++] << 8;
     motor1.step_number |= flash_data[index++] << 16;
     motor1.step_number |= flash_data[index++] << 24;

     motor2.step_number = flash_data[index++];
     motor2.step_number |= flash_data[index++] << 8;
     motor2.step_number |= flash_data[index++] << 16;
     motor2.step_number |= flash_data[index++] << 24;

     servo1.angle = flash_data[index++];
     servo1.angle |= flash_data[index++] << 8;

     servo2.angle = flash_data[index++];
     servo2.angle |= flash_data[index++] << 8;

}

void saveMotorPositions()
{
    int index = 0;
    unsigned char data[12];

    data[index++] = (motor1.step_number) & 0xff;
    data[index++] = (motor1.step_number >> 8) & 0xff;
    data[index++] = (motor1.step_number >> 16) & 0xff;
    data[index++] = (motor1.step_number >> 24) & 0xff;

    data[index++] = (motor2.step_number) & 0xff;
    data[index++] = (motor2.step_number >> 8) & 0xff;
    data[index++] = (motor2.step_number >> 16) & 0xff;
    data[index++] = (motor2.step_number >> 24) & 0xff;

    data[index++] = (servo1.angle) & 0xff;
    data[index++] = (servo1.angle >> 8) & 0xff;

    data[index++] = (servo2.angle) & 0xff;
    data[index++] = (servo2.angle >> 8) & 0xff;

    reWriteFlash(data, index, SECTOR6_ADDRESS);

}

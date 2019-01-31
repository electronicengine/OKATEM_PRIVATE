#include "motorops.h"
#include "main.h"
#include "motor.h"
#include "tim.h"
#include "flash.h"


volatile int speed = 0;


void motorOps(void const * argument)
{

    //  (1/(108.000.000/(psc+1))*period) -> timer width

    mprintf("motorOps\r\n");


    getInitialPositions();

    while(1)
    {


        driveStepMotors();

        driveServoMotors();

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


    if(motor1.direction == FORWARD)
    {

        if(motor1.step_number < motor1.max_step_number)
        {
            motor1Drive(FORWARD);

//            xSemaphoreTake(controlMutexHandle, portMAX_DELAY);

                speed = motor1.speed;
                motor1.step_number++;

//            xSemaphoreGive(controlMutexHandle);
        }
        else
        {
            motor1Drive(STOP);
        }

    }
    else if(motor1.direction == BACKWARD)
    {

        if(motor1.step_number > 0)
        {
            motor1Drive(BACKWARD);

//            xSemaphoreTake(controlMutexHandle, portMAX_DELAY);

                speed = motor1.speed;

                if(motor1.step_number != 0)
                    motor1.step_number--;

//            xSemaphoreGive(controlMutexHandle);
        }
        else
        {
            motor1Drive(STOP);
        }

    }
    else
    {
        motor1Drive(STOP);
    }



    if(motor2.direction == FORWARD )
    {

        if(motor2.step_number != 0)
        {
            motor2Drive(FORWARD);


//            xSemaphoreTake(controlMutexHandle, portMAX_DELAY);
                speed = motor1.speed;

                if(motor2.step_number != 0)
                    motor2.step_number--;
//            xSemaphoreGive(controlMutexHandle);
        }
        else
        {
            motor2Drive(STOP);
        }

    }
    else if(motor2.direction == BACKWARD)
    {

        if(motor2.step_number < motor2.max_step_number)
        {
            motor2Drive(BACKWARD);

//            xSemaphoreTake(controlMutexHandle, portMAX_DELAY);

                speed = motor1.speed;

                motor2.step_number++;

//            xSemaphoreGive(controlMutexHandle);
        }
        else
        {
            motor2Drive(STOP);
        }
    }
    else
    {
        motor2Drive(STOP);
    }




}

void driveServoMotors()
{
    static int counter1 = 0;
    static int counter2 = 0;

    static int servo2_degree = 0;
    static int servo1_degree = 0;

    if(servo2.angle != 0 /*&& servo2.angle <= servo2.top && servo2.angle >= servo2.bottom */)
    {
       HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

       xSemaphoreTake(controlMutexHandle, portMAX_DELAY);

         servo2_degree = servo2.angle;

       xSemaphoreGive(controlMutexHandle);


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

    if(servo1.angle != 0  /*&& servo1.angle <= servo1.top && servo1.angle >= servo1.bottom*/)
    {
       HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

       xSemaphoreTake(controlMutexHandle, portMAX_DELAY);

         servo1_degree = servo1.angle;

       xSemaphoreGive(controlMutexHandle);


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



void getInitialPositions()
{
    uint8_t setting = 0;


    while(1)
    {

        xSemaphoreTake(controlMutexHandle, portMAX_DELAY);
            setting = setting_enable;
        xSemaphoreGive(controlMutexHandle);


        if(setting == 0xff)
        {

            xSemaphoreTake(controlMutexHandle, portMAX_DELAY);

                motor1.step_number = ControlData->y_position;
                motor1.max_step_number = ControlData->step_motor1_step;

                motor2.step_number = ControlData->x_position;
                motor2.max_step_number = ControlData->step_motor2_step;

                servo1.top =  ControlData->servo_motor1_top_degree;
                servo1.bottom = ControlData->servo_motor1_bottom_degree;

                servo2.top =  ControlData->servo_motor2_top_degree;
                servo2.bottom = ControlData->servo_motor2_bottom_degree;

            xSemaphoreGive(controlMutexHandle);




            break;
        }
        else
        {
            xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

                EnvironmentData->step_motor1_step = 0xffffffff;
                EnvironmentData->step_motor2_step = 0xffffffff;
                EnvironmentData->servo_motor1_degree = 0xff;
                EnvironmentData->servo_motor2_degree = 0xff;

            xSemaphoreGive(spiMutexHandle);

        }

        osDelay(3);


    }


    osDelay(250);
}



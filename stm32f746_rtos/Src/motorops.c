#include "motorops.h"
#include "main.h"
#include "motor.h"
#include "tim.h"
#include "flash.h"


volatile int speed = 0;
volatile uint32_t step1_desired_step = 0;
volatile uint32_t step2_desired_step = 0;

void motorOps(void const * argument)
{

    //  (1/(108.000.000/(psc+1))*period) -> timer width

    mprintf("motorOps\r\n");

    getInitialPositions();

    while(1)
    {

        if(motor1.desired_step != 0)
            step1_desired_step = motor1.desired_step;

        if(motor2.desired_step != 0)
            step2_desired_step = motor2.desired_step;


        if(step1_desired_step != 0 || step2_desired_step != 0)
            driveStepMotorswithPosition();
        else
            driveStepMotorswithDirection();

        driveServoMotors();

        putMotorInformationstoEnvironmentData();

        osDelay(2 + speed);

    }
}

void driveStepMotorswithDirection()
{

    if(motor1.direction == FORWARD)
    {

        if(motor1.step_number < motor1.max_step_number)
        {
            motor1Drive(FORWARD);


            speed = motor1.speed;
            motor1.step_number++;

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


            speed = motor1.speed;

            if(motor1.step_number != 0)
                motor1.step_number--;

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


            speed = motor1.speed;

            if(motor2.step_number != 0)
                motor2.step_number--;

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


                speed = motor1.speed;

                motor2.step_number++;

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

    if(servo1.angle != 0  /*&& servo1.angle <= servo1.top && servo1.angle >= servo1.bottom*/)
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



void getInitialPositions()
{


    while(1)
    {



        if(setting_enable == 0xff)
        {
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



void putMotorInformationstoEnvironmentData()
{

    uint8_t step_motor_breaks = 0;

    if(HAL_GPIO_ReadPin(STEP1_BREAK_GPIO_Port, STEP1_BREAK_Pin) == GPIO_PIN_SET)
        step_motor_breaks =  1;
    else
        step_motor_breaks =  0;


    if(HAL_GPIO_ReadPin(STEP2_BREAK_GPIO_Port, STEP2_BREAK_Pin) == GPIO_PIN_SET)
        step_motor_breaks += 240;
    else
        step_motor_breaks += 0;

    xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

        EnvironmentData->step_motor1_step = motor1.step_number;
        EnvironmentData->step_motor2_step = motor2.step_number;
        EnvironmentData->servo_motor1_degree = servo1.angle;
        EnvironmentData->servo_motor2_degree = servo2.angle;
        EnvironmentData->step_motor_breaks = step_motor_breaks;

    xSemaphoreGive(spiMutexHandle);

}

void driveStepMotorswithPosition()
{

    if(motor1.step_number < step1_desired_step)
    {
        if(motor1.max_step_number > motor1.step_number)
        {
            motor1Drive(FORWARD);

            speed = motor1.speed;
            motor1.step_number++;
        }
    }
    else if(motor1.step_number > step1_desired_step)
    {

        if(motor1.step_number > 0)
        {
            motor1Drive(BACKWARD);

            speed = motor1.speed;
            motor1.step_number--;
        }
    }
    else
    {
        step1_desired_step = 0;
        motor1Drive(STOP);
    }

    if(motor2.step_number < step2_desired_step)
    {
        if(motor2.max_step_number > motor2.step_number)
        {
            motor2Drive(FORWARD);

            speed = motor2.speed;
            motor2.step_number++;
        }
    }
    else if(motor2.step_number > step2_desired_step)
    {

        if(motor2.step_number > 0)
        {
            motor2Drive(BACKWARD);

            speed = motor2.speed;
            motor2.step_number--;
        }
    }
    else
    {
        step2_desired_step = 0;
        motor2Drive(STOP);
    }

}

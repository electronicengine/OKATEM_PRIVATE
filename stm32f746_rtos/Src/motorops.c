#include "motorops.h"
#include "main.h"



void motorOps(void const * argument)
{

    //  (1/(108.000.000/(psc+1))*period) -> timer width



    int counter1 = 0;
    int counter2 = 0;

    int servo2_degree = 0;
    int servo1_degree = 0;

    int speed = 0;
    int pwm = 80;


    int step_motor1_last_direction;
    int step_motor2_last_direction;
    int step_motor1_break;
    int step_motor2_break;

    short int offside_step1;
    short int offside_step2;
    short int offside_available_step1 = 0;
    short int offside_available_step2 = 0;


    mprintf("motorOps\r\n");

    while(1)
    {

        step_motor1_break = HAL_GPIO_ReadPin(STEP1_BREAK_GPIO_Port, STEP1_BREAK_Pin);
        step_motor2_break = HAL_GPIO_ReadPin(STEP2_BREAK_GPIO_Port, STEP2_BREAK_Pin);

//        if(!step_motor1_break && !offside_available_step1)
//        {
//            offside_step1 == step_motor1_last_direction;
//            offside_available_step1 = 1;

//        }else if(step_motor1_break)
//        {
//            offside_step1 = 0;
//            offside_available_step1 = 0;
//        }


//        if(!step_motor2_break && !offside_available_step2)
//        {
//            offside_step2 == step_motor2_last_direction;
//            offside_available_step2 = 1;

//        }else if(step_motor2_break)
//        {
//            offside_step2 = 0;
//            offside_available_step2 = 0;
//        }

        if(motor1.direction == FORWARD)
        {
//            if(offside_step1 != FORWARD)
//            {
                motor1Drive(FORWARD);
                speed = motor1.speed;
//            }
             step_motor1_last_direction = FORWARD;

        }
        else if(motor1.direction == BACKWARD)
        {
//            if(offside_step1 == BACKWARD)
//            {
                motor1Drive(BACKWARD);
                speed = motor1.speed;
//            }
            step_motor1_last_direction = BACKWARD;
        }
        else
        {
            motor1Drive(STOP);
        }


        if(motor2.direction == FORWARD )
        {
//            if(offside_step2 != FORWARD)
//            {
                motor2Drive(FORWARD);
                speed = motor1.speed;
//            }
            step_motor2_last_direction = FORWARD;
        }
        else if(motor2.direction == BACKWARD)
        {
//            if(offside_step2 != BACKWARD)
//            {
                motor2Drive(BACKWARD);
                speed = motor1.speed;
//            }
            step_motor2_last_direction = BACKWARD;
        }
        else
        {
            motor2Drive(STOP);
        }



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

        osDelay(2 + speed);


//        pwm++;

//        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (int)((double)(pwm)*((double)(215-60)/150) + 60));


//        if(pwm >= 120)
//            pwm = 80;

//        osDelay(100);

    }
}

#include "motorops.h"
#include "main.h"



void motorOps(void const * argument)
{

//    int pwm = 65; // 65 - 215

    static int counter1 = 0;
    static int counter2 = 0;

    static int servo2_degree = 0;
    static int servo1_degree = 0;

    static int speed = 0;


    mprintf("motorOps\r\n");


    while(1)
    {


//        mprintf("1-%d\r\n", HAL_GPIO_ReadPin(STEP1_BREAK_GPIO_Port, STEP1_BREAK_Pin));
//        mprintf("2-%d\r\n", HAL_GPIO_ReadPin(STEP2_BREAK_GPIO_Port, STEP2_BREAK_Pin));


        if(HAL_GPIO_ReadPin(STEP1_BREAK_GPIO_Port, STEP1_BREAK_Pin))
        {

            if(motor1.direction == FORWARD)
            {
                motor1Drive(FORWARD);
                speed = motor1.speed;
            }
            else if(motor1.direction == BACKWARD)
            {
                motor1Drive(BACKWARD);
                speed = motor1.speed;
            }
            else
            {
                motor1Drive(STOP);
            }

        }

        if(HAL_GPIO_ReadPin(STEP2_BREAK_GPIO_Port, STEP2_BREAK_Pin))
        {

            if(motor2.direction == FORWARD)
            {
                motor2Drive(FORWARD);
                speed = motor1.speed;
            }
            else if(motor2.direction == BACKWARD)
            {
                motor2Drive(BACKWARD);
                speed = motor1.speed;
            }
            else
            {
                motor2Drive(STOP);
            }
        }


        if(servo2.angle != 0)
        {
           HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

           servo2_degree = servo2.angle;

           counter2 = 0;
           speed = 1;
        }

        if(counter2 <= 300)
        {
          counter2 ++;
          __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, (int)((double)(servo2_degree)*((double)(215-60)/150) + 60));
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

        if(counter1 <= 300)
        {
          counter1 ++;
          __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (int)((double)(servo1_degree)*((double)(215-60)/150) + 60));
        }
        else
        {
           HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
        }

        osDelay(2 + speed);

    }

}



#include "servo.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"

void driveServo1(int Degree)
{

    if(Degree != 0)
    {
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (Degree)*((double)(215-60)/150) + 60); // (servo1_degree)*((double)(215-60)/150) + 60) and for own servo

    }

}

void driveServo2(int Degree)
{

    static int counter2 = 0;
    static int servo2_degree = 0;


    if(Degree != 0  /*&& servo1.angle <= servo1.top && servo1.angle >= servo1.bottom*/)
    {
       HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);


         servo2_degree = Degree;



       counter2 = 0;
    }


    if(counter2 <= 100)
    {
      counter2 ++;
      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (servo2_degree)*((double)(215-60)/150) + 60) ; // (int)((double)(servo1_degree)*((double)(200-100)/150) + 100));and for own servo
    }
    else
    {
       HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    }

}

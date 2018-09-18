#include "motorops.h"
#include "main.h"



void motorOps(void const * argument)
{

    int pwm = 45;

    mprintf("motorOps\r\n");



    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, pwm);
    pwm++;
    osDelay(100);

    if(pwm == 153)
      pwm = 45;


    while(1)
    {



      if(motor1.direction == FORWARD)
      {
        motor1Drive(FORWARD);
      }

      if(motor1.direction == BACKWARD)
      {
        motor1Drive(BACKWARD);
      }

      if(motor2.direction == FORWARD)
      {
        motor2Drive(FORWARD);
      }

      if(motor2.direction == BACKWARD)
      {
        motor2Drive(BACKWARD);
      }

      osDelay(2 + motor1.speed);


    }

}

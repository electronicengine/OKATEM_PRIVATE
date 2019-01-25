

#include "motor.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"

const int reductor_coefficient = 300; // 500/1.8 = 355.55555

uint32_t step_num = 5000;
uint32_t counter = 0;

void motorInit()
{
    HAL_TIM_Base_Start_IT(&htim2);
}

void  motor1Drive(int Direction)
{
    static volatile int phase = 1;

    if(Direction == FORWARD)
    {

        HAL_GPIO_WritePin(ENABLE_STEP1_GPIO_Port, ENABLE_STEP1_PIN,GPIO_PIN_SET);

          if(phase  == 1)
          {


              HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_RESET);
              phase ++;

          }
          else if(phase  == 2)
          {

              HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_RESET);
              phase ++;

          }
          else if(phase  == 3)
          {

              HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_RESET);
              phase ++;

          }
          else if(phase  == 4)
          {

              HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_RESET);
              phase  = 1;

          }


    }

    if(Direction == BACKWARD)
    {

        HAL_GPIO_WritePin(ENABLE_STEP1_GPIO_Port, ENABLE_STEP1_PIN,GPIO_PIN_SET);


        if(phase  == 1)
        {

            HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_RESET);


            phase ++;

        }
        else if(phase  == 2)
        {

            HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_RESET);


            phase ++;

        }
        else if(phase  == 3)
        {

            HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_RESET);

            phase ++;

        }
        else if(phase  == 4)
        {

            HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_RESET);
            phase  = 1;

        }

    }

    if(Direction == STOP)
    {
        HAL_GPIO_WritePin(ENABLE_STEP1_GPIO_Port, ENABLE_STEP1_PIN,GPIO_PIN_RESET);

        HAL_GPIO_WritePin(STEP1_AI1_GPIO_Port, STEP1_AI1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(STEP1_AI2_GPIO_Port, STEP1_AI2_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(STEP1_BI1_GPIO_Port, STEP1_BI1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(STEP1_BI2_GPIO_Port, STEP1_BI2_Pin, GPIO_PIN_RESET);
    }


}

void motor2Drive(int Direction)
{

    static volatile int phase = 1;

    if(Direction == FORWARD)
    {

        HAL_GPIO_WritePin(ENABLE_STEP2_GPIO_Port, ENABLE_STEP2_PIN,GPIO_PIN_SET);

          if(phase  == 1)
          {


              HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_RESET);
              phase ++;

          }
          else if(phase  == 2)
          {

              HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_RESET);
              phase ++;

          }
          else if(phase  == 3)
          {

              HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_RESET);
              phase ++;

          }
          else if(phase  == 4)
          {

              HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_RESET);

              HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_SET);
              HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_RESET);
              phase  = 1;

          }


    }

    if(Direction == BACKWARD)
    {

        HAL_GPIO_WritePin(ENABLE_STEP2_GPIO_Port, ENABLE_STEP2_PIN,GPIO_PIN_SET);


        if(phase  == 1)
        {

            HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_RESET);


            phase ++;

        }
        else if(phase  == 2)
        {

            HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_RESET);


            phase ++;

        }
        else if(phase  == 3)
        {

            HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_RESET);

            phase ++;

        }
        else if(phase  == 4)
        {

            HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_RESET);
            phase  = 1;

        }

    }

    if(Direction == STOP)
    {
        HAL_GPIO_WritePin(ENABLE_STEP2_GPIO_Port, ENABLE_STEP2_PIN,GPIO_PIN_SET);

        HAL_GPIO_WritePin(STEP2_AI1_GPIO_Port, STEP2_AI1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(STEP2_AI2_GPIO_Port, STEP2_AI2_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(STEP2_BI1_GPIO_Port, STEP2_BI1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(STEP2_BI2_GPIO_Port, STEP2_BI2_Pin, GPIO_PIN_RESET);
    }

}


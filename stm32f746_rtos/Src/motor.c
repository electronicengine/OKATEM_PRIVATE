

#include "motor.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"

const int reductor_coefficient = 300; // 500/1.8 = 355.55555


void motorInit()
{
    HAL_TIM_Base_Start_IT(&htim2);
}

void  motor1Drive(int Direction)
{
    static volatile int phase = 1;

        if(Direction == FORWARD)
        {

//            motor2.degree--;

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


//    if(motor1.degree <= 0)
//    {
//        motor1.direction = STOP;
//        motor1.degree = 0;

//    }
}

void motor2Drive()
{

    static volatile int phase = 1;

//        if(motor2.direction == FORWARD && motor2.degree >= 0)
//        {

//            motor2.degree--;

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


//        }


//    if(motor1.degree <= 0)
//    {
//        motor1.direction = STOP;
//        motor1.degree = 0;

//    }

}


void  motor3Drive()
{
    static volatile int phase = 1;

//        if(motor2.direction == FORWARD && motor2.degree >= 0)
//        {

//            motor2.degree--;

              if(phase  == 1)
              {


                  HAL_GPIO_WritePin(STEP3_AI1_GPIO_Port, STEP3_AI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_AI2_GPIO_Port, STEP3_AI2_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP3_BI1_GPIO_Port, STEP3_BI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_BI2_GPIO_Port, STEP3_BI2_Pin, GPIO_PIN_RESET);
                  phase ++;

              }
              else if(phase  == 2)
              {

                  HAL_GPIO_WritePin(STEP3_AI1_GPIO_Port, STEP3_AI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_AI2_GPIO_Port, STEP3_AI2_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP3_BI2_GPIO_Port, STEP3_BI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_BI1_GPIO_Port, STEP3_BI1_Pin, GPIO_PIN_RESET);
                  phase ++;

              }
              else if(phase  == 3)
              {

                  HAL_GPIO_WritePin(STEP3_AI2_GPIO_Port, STEP3_AI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_AI1_GPIO_Port, STEP3_AI1_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP3_BI2_GPIO_Port, STEP3_BI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_BI1_GPIO_Port, STEP3_BI1_Pin, GPIO_PIN_RESET);
                  phase ++;

              }
              else if(phase  == 4)
              {

                  HAL_GPIO_WritePin(STEP3_AI2_GPIO_Port, STEP3_AI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_AI1_GPIO_Port, STEP3_AI1_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP3_BI1_GPIO_Port, STEP3_BI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP3_BI2_GPIO_Port, STEP3_BI2_Pin, GPIO_PIN_RESET);
                  phase  = 1;

              }


//        }


//    if(motor1.degree <= 0)
//    {
//        motor1.direction = STOP;
//        motor1.degree = 0;

//    }
}


void motor4Drive()
{
    static volatile int phase = 1;

//        if(motor2.direction == FORWARD && motor2.degree >= 0)
//        {

//            motor2.degree--;

              if(phase  == 1)
              {


                  HAL_GPIO_WritePin(STEP4_AI1_GPIO_Port, STEP4_AI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_AI2_GPIO_Port, STEP4_AI2_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP4_BI1_GPIO_Port, STEP4_BI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_BI2_GPIO_Port, STEP4_BI2_Pin, GPIO_PIN_RESET);
                  phase ++;

              }
              else if(phase  == 2)
              {

                  HAL_GPIO_WritePin(STEP4_AI1_GPIO_Port, STEP4_AI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_AI2_GPIO_Port, STEP4_AI2_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP4_BI2_GPIO_Port, STEP4_BI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_BI1_GPIO_Port, STEP4_BI1_Pin, GPIO_PIN_RESET);
                  phase ++;

              }
              else if(phase  == 3)
              {

                  HAL_GPIO_WritePin(STEP4_AI2_GPIO_Port, STEP4_AI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_AI1_GPIO_Port, STEP4_AI1_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP4_BI2_GPIO_Port, STEP4_BI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_BI1_GPIO_Port, STEP4_BI1_Pin, GPIO_PIN_RESET);
                  phase ++;

              }
              else if(phase  == 4)
              {

                  HAL_GPIO_WritePin(STEP4_AI2_GPIO_Port, STEP4_AI2_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_AI1_GPIO_Port, STEP4_AI1_Pin, GPIO_PIN_RESET);

                  HAL_GPIO_WritePin(STEP4_BI1_GPIO_Port, STEP4_BI1_Pin, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(STEP4_BI2_GPIO_Port, STEP4_BI2_Pin, GPIO_PIN_RESET);
                  phase  = 1;

              }


//        }


//    if(motor1.degree <= 0)
//    {
//        motor1.direction = STOP;
//        motor1.degree = 0;

//    }
}



void driveMotor()
{

//    if(motor1.direction == FORWARD || motor1.direction == BACKWARD)
//       motor1Drive();

//    if(motor2.direction == FORWARD || motor2.direction == BACKWARD)
//       motor2Drive();

//    if(motor3.direction == FORWARD || motor3.direction == BACKWARD)
//       motor3Drive();

//    if(motor4.direction == FORWARD || motor4.direction == BACKWARD)
//       motor4Drive();


}



int moveMotor(int Motor, int Degree, short int Direction)
{


    if(motor1.direction == STOP)
    {
        switch(Motor)
        {

            case MOTOR1:
                motor1.degree = reductor_coefficient * Degree;
                motor1.direction = Direction;

                break;

            case MOTOR2:
                motor2.degree = reductor_coefficient * Degree;
                motor2.direction = Direction;

                break;

            case MOTOR3:
                motor3.degree = reductor_coefficient * Degree;
                motor3.direction = Direction;

                break;


            case MOTOR4:
                motor4.degree = reductor_coefficient * Degree;
                motor4.direction = Direction;

                break;
        }

        return SUCCESS;
    }
    else
    {

        return ERROR;
    }

}

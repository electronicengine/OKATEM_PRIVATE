
#ifndef __motor_H
#define __motor_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "main.h"


#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 3
#define MOTOR4 4

#define FORWARD 1
#define BACKWARD 2
#define STOP 0

 struct Step_Motor {
   volatile int direction;
   volatile int speed;
   volatile uint32_t step_number;
 }motor1, motor2, motor3, motor4;


 struct Servo_motor {
   volatile int angle;
   volatile int speed;
 }servo1, servo2;


void motorInit();

void driveMotor();

void motor1Drive(int Direction);
void motor2Drive(int Direction);

#ifdef __cplusplus
}
#endif
#endif 


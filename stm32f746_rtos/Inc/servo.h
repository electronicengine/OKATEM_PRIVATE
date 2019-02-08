
#ifndef __servo_H
#define __servo_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "main.h"


// struct Servo_motor {
//   volatile int angle;
//   volatile int speed;
//   volatile int top;
//   volatile int bottom;
// }servo1, servo2;

void driveServo1(int Degree);
void driveServo2(int Degree);

#ifdef __cplusplus
}
#endif
#endif 


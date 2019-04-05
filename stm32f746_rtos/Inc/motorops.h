#ifndef __motorops_H
#define __motorops_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"
#include <string.h>
#include "freertos.h"


#define RESPONSE_TIME            10
#define SERVO_PWM_COEFFICIENT   1.033f
#define SERVO_MIN_PWM_DUTY      60

#define SERVO_DRIVE_TIMEOUT     500
#define MIN_SPEED_TRESHOLD      3

typedef enum{

     Direction,
     Position

 }DriveCommand;

void motorOps(void const * argument);
void operate();
void putMotorInformationstoEnvironmentData();

void driveStep1WithPosition();
void driveStep2WithPosition();

DriveCommand checkIfDriveCommand();
void driveStep1WithDirection();
void driveStep2WithDirection();

void driveServoMotor1();
void driveServoMotor2();


void getInitialPositions();


#ifdef __cplusplus
}
#endif
#endif

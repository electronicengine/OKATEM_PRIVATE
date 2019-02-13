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




void motorOps(void const * argument);

void putMotorInformationstoEnvironmentData();
void driveStepMotorswithPosition();
void driveStepMotorswithDirection();
void driveServoMotors();
void getInitialPositions();


#ifdef __cplusplus
}
#endif
#endif

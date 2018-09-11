#ifndef __spiops_H
#define __spiops_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"
#include <string.h>
#include "freertos.h"

void spiComOps(void const * argument);

HAL_StatusTypeDef checkIfUpdateData();
HAL_StatusTypeDef checkIfControlData();

HAL_StatusTypeDef confirmUpdateDataAccuracy();

void putControlDataResponse();
void putUpdateDataResponse();
void processUpdateData();
void processControlData();
void putEnvironmentData();

void writeUpdateFileToFlash(unsigned char *UpdateFile);


#ifdef __cplusplus
}
#endif
#endif // SENSOR_H

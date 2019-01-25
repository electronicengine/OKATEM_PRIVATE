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

HAL_StatusTypeDef checkIfControlData();

void putControlDataResponse();
void processControlData();
void putEnvironmentData();
void recieveControlData(SPI_TRANSFER_FORMAT *SpiRxData);



#ifdef __cplusplus
}
#endif
#endif // SENSOR_H

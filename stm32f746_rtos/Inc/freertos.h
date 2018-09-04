#ifndef __freertos_H
#define __freertos_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "gps.h"
#include "sensor.h"
#include "motor.h"
#include <stdarg.h>
#include <stdio.h>
#include "usart.h"
#include "spi.h"
#include "sfp.h"
#include "tim.h"
#include "gpsops.h"
#include "stdlib.h"


osThreadId gpsThreadHandle;
osThreadId sensorThreadHandle;
osThreadId spiComThreadHandle;
osThreadId motorThreadHandle;


osMutexId spiMutexHandle;
osMutexId uartMutexHandle;
osMutexId memoryMutexHandle;

osSemaphoreId spiSemaphoreHandle;
osSemaphoreId uartSemaphoreHandle;


SPI_TRANSFER_FORMAT *SpiCheckData;
SPI_TRANSFER_FORMAT *SpiTxData;
SPI_TRANSFER_FORMAT *SpiRxData;
ENVIRONMENT_DATA_FORMAT *EnvironmentData;

CONTROL_DATA_FORMAT *ControlData;
UPDATE_FILE_FORMAT *UpdateFile;


void MX_FREERTOS_Init(void);
void mprintf(const char *fmt, ...);
unsigned char rx_buf;





#ifdef __cplusplus
}
#endif
#endif // SENSOR_H



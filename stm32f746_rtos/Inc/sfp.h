#ifndef __sfp_H
#define __sfp_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"
#include <string.h>
#include <inttypes.h>


int getSfpTemperature();
float getSfpVcc();
float getSfpTxBias();
float getSfpTransmitterPower();
float getSfpReceiverPower();

#ifdef __cplusplus
}
#endif
#endif // SENSOR_H

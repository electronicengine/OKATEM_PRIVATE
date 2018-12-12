
#ifndef __spicom_H
#define __spicom_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ---------------Src/sensor.c--------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"

 typedef struct{
     unsigned char *file_pointer;
     uint32_t file_size;
     short int receive_complited;
 }Update_File;

Update_File processUpdateData();
HAL_StatusTypeDef confirmUpdateDataAccuracy();
HAL_StatusTypeDef checkIfUpdateData();
void putUpdateDataResponse();

int checkDataAvailable();
int setDataRecieved();
void updateFinished();

#ifdef __cplusplus
}
#endif
#endif /*__ spicom_H */


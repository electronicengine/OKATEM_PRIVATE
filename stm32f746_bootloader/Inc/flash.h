
#ifndef __flash_H
#define __flash_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "main.h"

#define APPLICATION_ADDRESS        0x08010000
#define UPDATE_FILE_ADRESS         0x08080000


void writeFlash(uint8_t Data, long Address);
uint8_t readFlash(int Address);
void loadUpdateFile(unsigned char* Buffer, uint32_t Size);



#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */


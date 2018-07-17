#ifndef __gps_H
#define __gps_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"
#include <string.h>



#define GPS_READY 1
#define GPS_OK 0
#define GPS_BUSY 2
#define GPS_FAIL -1


struct gps_data
{
    volatile unsigned char gpgga_body[100];
    int gpgga_size;

    volatile unsigned char gpgll_body[100];
    int gpgll_size;

    volatile unsigned char gpgsa_body[100];
    int gpgsa_size;

    volatile unsigned char gprmc_body[100];
    int gprmc_size;

}gpsData;

void gpsInit();
void receiveGpsData();
void enableGps();
int  checkGpsData();
#ifdef __cplusplus
}
#endif
#endif // SENSOR_H

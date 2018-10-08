#ifndef __sensor_H
#define __sensor_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "main.h"
#include <string.h>
#include <inttypes.h>

#define FAIL -1
#define OK    0
#define SENSOR_READY 1
#define SENSOR_BUSY 2
#define SENSOR_FAIL 3

 struct sensor_values
 {
     long pressure;
     long altitude;
     int temperature;
     unsigned char wheather_condition;
     long compass_degree;

 }sensorValues;

 struct Calibration {
   volatile int available;

 }calibration;


 void sensorInit();

 void readAllSensors();

 void WakeUpSensor();
 void calibrateCompass();

 uint8_t checkPressure();
 uint8_t checkAltitude();
 uint8_t checkTemperature();
 uint8_t checkCompass();
 uint8_t checkWheather();

 long readPressure();
 long readAltitude();
 int readTemperature();
 long int readCompass();
 unsigned char readWheather();
 int SleepSensor();



#ifdef __cplusplus
}
#endif
#endif // SENSOR_H

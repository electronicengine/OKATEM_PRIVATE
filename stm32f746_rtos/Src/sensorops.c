#include "sensorops.h"


/* sensorOps function */
void sensorOps(void const * argument)
{

  mprintf("sensorOps\r\n");

  sensorInit();

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);




//  calibrateCompass();

  while(1)
  {
      readAllSensors();


      xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

      EnvironmentData -> sensor_data.temperature = sensorValues.temperature;
      EnvironmentData -> sensor_data.pressure = sensorValues.pressure;
      EnvironmentData -> sensor_data.altitude = sensorValues.altitude;
      EnvironmentData -> sensor_data.wheather_condition = sensorValues.wheather_condition;
      EnvironmentData -> sensor_data.compass_degree = sensorValues.compass_degree;

      xSemaphoreGive(spiMutexHandle);




  }

}

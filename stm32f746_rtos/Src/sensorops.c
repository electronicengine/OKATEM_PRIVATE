#include "sensorops.h"


/* sensorOps function */
void sensorOps(void const * argument)
{

  mprintf("sensorOps\r\n");

//  sensorInit();


  while(1)
  {


      if(calibration.available == 1)
      {
          mprintf("Sensor Calibration Started. \r\n");

          calibration.available  = 0;
          calibrateCompass();
      }
      else
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

}

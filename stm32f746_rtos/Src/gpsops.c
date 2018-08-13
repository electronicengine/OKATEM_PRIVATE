#include "gpsops.h"
#include "stdlib.h"


void UART4_IRQHandler(void)
{


    HAL_UART_IRQHandler(&huart4);

    xSemaphoreGiveFromISR(uartSemaphoreHandle, NULL);

}



void gpsOps(void const *argument)
{

    mprintf("gpsOps\r\n");

    unsigned char rx_data;

    gpsInit();

  while(1)
  {

      if( xSemaphoreTake(uartSemaphoreHandle, 1000) == pdPASS)
      {


        if(checkGpsData() == GPS_READY)
        {

               xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

               for(int i=0; i<99; i++)
                   EnvironmentData -> gps_string[i] = gpsData.gprmc_body[i];

               xSemaphoreGive(spiMutexHandle);



           HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);

           enableGps();

        }


          receiveGpsData();

          HAL_UART_Receive_IT(&huart4, (uint8_t *)&rx_data, 1);


      }
      else
      {

          mprintf("gpsOps Crash \r\n");

      }

  }

}

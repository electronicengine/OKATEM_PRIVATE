/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
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


osThreadId gpsThreadHandle;
osThreadId sensorThreadHandle;
osThreadId spiComThreadHandle;
osThreadId logThreadHandle;


osMutexId spiMutexHandle;
osMutexId uartMutexHandle;
osMutexId memoryMutexHandle;

osSemaphoreId spiSemaphoreHandle;
osSemaphoreId uartSemaphoreHandle;

struct SPI_RX_FORMAT
{
    uint8_t garbage1[47];
    uint32_t x_position;
    uint32_t y_position;
    uint32_t z_position;

    uint8_t step_motor1_direction;
    uint8_t step_motor2_direction;
    uint8_t step_motor3_direction;
    uint8_t step_motor4_direction;
    uint8_t servo_motor1_direction;
    uint8_t servo_motor2_direction;

    uint8_t step_motor1_speed;
    uint8_t step_motor2_speed;
    uint8_t step_motor3_speed;
    uint8_t step_motor4_speed;
    uint8_t servo_motor1_degree;
    uint8_t servo_motor2_degree;

    uint16_t checksum;

    uint8_t garbage2[48];

}spi_rx_data, rx_data;

volatile struct SPI_TX_FORMAT
{

    unsigned char gps_data[100];

    uint32_t temperature;
    uint32_t compass_degree;
    uint32_t pressure;
    uint32_t altitude;

    unsigned char wheather_condition;

    uint16_t checksum;

}spi_tx_data,  tx_data;


//uint8_t rx[sizeof(spi_rx_data)];
//uint8_t tx[sizeof(spi_tx_data)];



void gpsOps(void const * argument);
void sensorOps(void const * argument);
void spiComOps(void const * argument);
void loggingOps(void const * argument);

void MX_FREERTOS_Init(void);
void mprintf(const char *fmt, ...);
unsigned char rx_buf;


void vprint(const char *fmt, va_list argp)
{
    char string[150];

    if(0 < vsprintf(string,fmt,argp)) // build string
       HAL_UART_Transmit(&huart1, (uint8_t*)string, strlen(string), 0xffffff); // send message via UART

}



void mprintf(const char *fmt, ...) // custom printf() function
{

    xSemaphoreTake(uartMutexHandle, 100);
    va_list argp;
    va_start(argp, fmt);
    vprint(fmt, argp);
    va_end(argp);
    xSemaphoreGive(uartMutexHandle);

}



void MX_FREERTOS_Init(void)
{

  osMutexDef(spiMutex);
  spiMutexHandle = osMutexCreate(osMutex(spiMutex));

  osMutexDef(uartMutex);
  uartMutexHandle = osMutexCreate(osMutex(uartMutex));

  osMutexDef(memoryMutex);
  memoryMutexHandle = osMutexCreate(osMutex(memoryMutex));

  osSemaphoreDef(uartSemaphore);
  uartSemaphoreHandle = osSemaphoreCreate(osSemaphore(uartSemaphore), 1);

  /* definition and creation of spiSemaphore */
  osSemaphoreDef(spiSemaphore);
  spiSemaphoreHandle = osSemaphoreCreate(osSemaphore(spiSemaphore), 1);

  /* definition and creation of gpsThread */
  osThreadDef(gpsThread, gpsOps, osPriorityAboveNormal, 0, 1024);
  gpsThreadHandle = osThreadCreate(osThread(gpsThread), NULL);

  /* definition and creation of sensorThread */
  osThreadDef(sensorThread, sensorOps, osPriorityBelowNormal, 0, 512);
  sensorThreadHandle = osThreadCreate(osThread(sensorThread), NULL);

  /* definition and creation of spiComThread */
  osThreadDef(spiComThread, spiComOps, osPriorityNormal, 0, 512);
  spiComThreadHandle = osThreadCreate(osThread(spiComThread), NULL);

//  osThreadDef(loggingThread, loggingOps, osPriorityNormal, 0, 512);
//  logThreadHandle = osThreadCreate(osThread(loggingThread), NULL);

}


void UART4_IRQHandler(void)
{

    long lSwitchRequired;

    HAL_UART_IRQHandler(&huart4);

    xSemaphoreGiveFromISR(uartSemaphoreHandle, NULL);

    if(lSwitchRequired)
        portYIELD_FROM_ISR(lSwitchRequired);


}

void SPI1_IRQHandler(void)
{


  long lSwitchRequired;


  HAL_SPI_IRQHandler(&hspi1);

  xSemaphoreGiveFromISR(spiSemaphoreHandle, NULL);

//  if(lSwitchRequired)
//      portYIELD_FROM_ISR(lSwitchRequired);

//  HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)&spi_tx_data, (uint8_t *)rx, sizeof(spi_tx_data));

}

void loggingOps(void const * argument)
{

    mprintf("logingOps\r\n");

    while(1)
    {
        mprintf("logingOps\r\n");
        osDelay(1000);
    }
}




void gpsOps(void const * argument)
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


               for(int i=0; i<100; i++)
                   spi_tx_data.gps_data[i] = gpsData.gprmc_body[i];



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

/* sensorOps function */
void sensorOps(void const * argument)
{


    int pwm=45;

  mprintf("sensorOps\r\n");

  sensorInit();

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  int ret;

//  calibrateCompass();

  while(1)
  {
      readAllSensors();


      xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

      spi_tx_data.temperature = sensorValues.temperature;
      spi_tx_data.pressure = sensorValues.pressure;
      spi_tx_data.altitude = sensorValues.altitude;
      spi_tx_data.wheather_condition = sensorValues.wheather_condition;
      spi_tx_data.compass_degree = sensorValues.compass_degree;

      spi_tx_data.checksum = 100;

      xSemaphoreGive(spiMutexHandle);


//      ret = getSfpTemperature();
//          mprintf("%d\r\n", ret);

//          osDelay(1000);

//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, pwm);
//      pwm++;
//      osDelay(100);

//      if(pwm == 153)
//          pwm = 45;



  }

}

/* spiComOps function */
void spiComOps(void const * argument)
{

    long token;
    int count = 0;
    int step = 0;

    HAL_SPI_StateTypeDef status;

    mprintf("spiOps\r\n");


    HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)&spi_tx_data, (uint8_t *)&spi_rx_data,  sizeof(spi_tx_data));


  while(1)
  {

      if( xSemaphoreTake(spiSemaphoreHandle, 1) == pdPASS)
      {

          status = HAL_SPI_GetState(&hspi1);
          if(status == HAL_SPI_STATE_READY)
          {




          }

         xSemaphoreTake(spiMutexHandle, portMAX_DELAY);

          tx_data = spi_tx_data;

         xSemaphoreGive(spiMutexHandle);




        HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)&tx_data, (uint8_t *)&spi_rx_data,  sizeof(spi_tx_data));


        if(spi_rx_data.step_motor1_direction == FORWARD)
        {
            motor1.direction = FORWARD;
        }
        else if(spi_rx_data.step_motor1_direction == BACKWARD)
        {
            motor1.direction = BACKWARD;
        }
        else
        {
            motor1.direction = STOP;
        }

        if(spi_rx_data.step_motor2_direction == FORWARD)
        {
            motor2.direction = FORWARD;
        }
        else if(spi_rx_data.step_motor2_direction == BACKWARD)
        {
            motor2.direction = BACKWARD;
        }
        else
        {
            motor2.direction = STOP;
        }



      }
      else
      {
          count ++;


          if(count >= 3)
          {


            if(motor1.direction == FORWARD)
            {
              motor1Drive(FORWARD);
            }

            if(motor1.direction == BACKWARD)
            {
              motor1Drive(BACKWARD);
            }

            if(motor2.direction == FORWARD)
            {
              motor2Drive(FORWARD);
            }

            if(motor2.direction == BACKWARD)
            {
              motor2Drive(BACKWARD);
            }


//            motor2Drive(FORWARD);

            count = 0;

          }
      }

  }

}

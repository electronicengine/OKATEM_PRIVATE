/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"
#include "eth.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "motor.h"
#include "sensor.h"
#include "gps.h"

#include <stdarg.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL -1

#define APPLICATION_ADDRESS        0x08010000
#define UPDATE_FILE_ADRESS         0x08080000


typedef void (*pFunction)(void);

void SystemClock_Config(void);
void vprint(const char *fmt, va_list argp);
void mprintf(const char *fmt, ...);
void EnablePrivilegedMode (void);
void bootRTOS();
int checkUpdate();
void loadUpdateFile();
void writeFlash(uint8_t Data, long Address);
uint8_t readFlash(int Address);




//void SPI1_IRQHandler(void)
//{

//  HAL_SPI_IRQHandler(&hspi1);

//}



int main(void)
{
    int ret = 0;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C2_Init();
    MX_I2C4_Init();
    MX_SPI1_Init();
    MX_TIM3_Init();
    MX_UART4_Init();
    MX_USART1_UART_Init();
    MX_TIM2_Init();

    mprintf("Bootloader Initializing...\r\n");


    HAL_Delay(5000);

//    HAL_FLASH_Unlock();
//    FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);
//    FLASH_Erase_Sector(FLASH_SECTOR_7, VOLTAGE_RANGE_3);
//    HAL_FLASH_Lock();


    ret = checkUpdate();

    if(ret == SUCCESS)
    {
        loadUpdateFile();
        HAL_Delay(1000);
        bootRTOS();
    }
    else
    {
        bootRTOS();
    }


}

int checkUpdate()
{

    uint32_t data;

    mprintf("Checking Firmware Update File...\r\n");

    data = readFlash(UPDATE_FILE_ADRESS) | (readFlash(UPDATE_FILE_ADRESS + 1) << 8)
            | readFlash(UPDATE_FILE_ADRESS + 2) << 16 | readFlash(UPDATE_FILE_ADRESS + 3) << 24;



    if(data == 0xffffffff)
    {
        mprintf("There is no update file in the flash\r\n");
        return FAIL;

    }
    else if(data > 512000 || data < 0)
    {
        mprintf("There is no update file in the flash\r\n");

        HAL_FLASH_Unlock();
        FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);
        FLASH_Erase_Sector(FLASH_SECTOR_7, VOLTAGE_RANGE_3);
        HAL_FLASH_Lock();

        return FAIL;
    }
    else
    {
        mprintf("A Update file has been found in the flash");
        return SUCCESS;
    }

}



void loadUpdateFile()
{
    uint32_t file_size;
    unsigned char *data;

    file_size = readFlash(UPDATE_FILE_ADRESS) | readFlash(UPDATE_FILE_ADRESS + 1) << 8
            | readFlash(UPDATE_FILE_ADRESS + 2) << 16 | readFlash(UPDATE_FILE_ADRESS + 3) << 24;


    mprintf("Update File Size : %d\r\n", file_size);

    data = malloc(file_size);


    HAL_FLASH_Unlock();
    FLASH_Erase_Sector(FLASH_SECTOR_2, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_3, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_4, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_5, VOLTAGE_RANGE_3);
    HAL_FLASH_Lock();

    HAL_Delay(1000);

    for(int i=0; i<file_size; i++)
        data[i] =readFlash(UPDATE_FILE_ADRESS + 4 + i);

    for(int i=0; i<file_size; i++)
        writeFlash(data[i], APPLICATION_ADDRESS + i);


    HAL_Delay(1000);

    HAL_FLASH_Unlock();
    FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_7, VOLTAGE_RANGE_3);
    HAL_FLASH_Lock();

    mprintf("UpdateFile has been writen on memory\r\n");


    free(data);


}



void bootRTOS()
{


    pFunction appEntry;
    uint32_t appStack;

    mprintf("Booting...\r\n");

//    EnablePrivilegedMode( ) ;


//    // Disable all interrupts
//    NVIC->ICER[ 0 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 1 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 2 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 3 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 4 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 5 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 6 ] = 0xFFFFFFFF ;
//    NVIC->ICER[ 7 ] = 0xFFFFFFFF ;


//    // Clear pendings
//    NVIC->ICPR[ 0 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 1 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 2 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 3 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 4 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 5 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 6 ] = 0xFFFFFFFF ;
//    NVIC->ICPR[ 7 ] = 0xFFFFFFFF ;


//    // Stop sys tick
//    SysTick->CTRL = 0 ;
//    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk ;

//    // Disable individual fault handlers if the bootloader used them.
//    SCB->SHCSR &= ~( SCB_SHCSR_USGFAULTENA_Msk | \
//                    SCB_SHCSR_BUSFAULTENA_Msk | \
//                    SCB_SHCSR_MEMFAULTENA_Msk ) ;

//    // Activate the MSP, if the core is found to currently run with the PSP.
//    if( CONTROL_SPSEL_Msk & __get_CONTROL( ) )
//    {  /* MSP is not active */
//     __set_CONTROL( __get_CONTROL( ) & ~CONTROL_SPSEL_Msk ) ;
//    }

//    __set_CONTROL(0);

    /* Get the application stack pointer (First entry in the application vector table) */
    appStack = (uint32_t) *((__IO uint32_t*)APPLICATION_ADDRESS);

    /* Get the application entry point (Second entry in the application vector table) */
    appEntry = (pFunction) *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);

//    /* Set the application stack pointer */
//    SYSCFG->MEMRMP = 0x01;

//    SCB->SHCSR &= ~( SCB_SHCSR_USGFAULTENA_Msk | \
//                     SCB_SHCSR_BUSFAULTENA_Msk | \
//                     SCB_SHCSR_MEMFAULTENA_Msk ) ;

    __set_MSP(appStack);

    /* Start the application */
    appEntry();

}




void writeFlash(uint8_t Data, long Address)
{

     HAL_FLASH_Unlock();
     HAL_FLASH_Program(TYPEPROGRAM_BYTE, Address , (uint8_t) Data);
     HAL_FLASH_Lock();
}

uint8_t readFlash(int Address)
{

    uint8_t flash_data;

    flash_data = *(uint8_t *)Address;

    return flash_data;

}



void EnablePrivilegedMode (void){
        __disable_irq();
        __set_CONTROL((__get_CONTROL( ))& 0xFFFFFFFE);  // enter priv mode
        __enable_irq();
}



void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
        HAL_UART_Transmit(&huart1, (uint8_t*)string, strlen(string), 0xffffff); // send message via UART
    }
}



void mprintf(const char *fmt, ...) // custom printf() function
{
    va_list argp;
    va_start(argp, fmt);
    vprint(fmt, argp);
    va_end(argp);
}



void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_UART4|RCC_PERIPHCLK_UART7
                              |RCC_PERIPHCLK_UART8|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_I2C3
                              |RCC_PERIPHCLK_I2C4;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart8ClockSelection = RCC_UART8CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }


  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);


  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);


  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}


void _Error_Handler(char *file, int line)
{

    mprintf("ERROR EVENT %s - %d\r\n", file, line);

}

void _Event_Handler(char *Event)
{
    mprintf("%s\r\n", Event);
}

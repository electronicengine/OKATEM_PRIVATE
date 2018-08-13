/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define WKUP_Pin GPIO_PIN_0
#define WKUP_GPIO_Port GPIOA
#define SFP_LOS_Pin GPIO_PIN_12
#define SFP_LOS_GPIO_Port GPIOF
#define LASER_EN_Pin GPIO_PIN_1
#define LASER_EN_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOB
#define STEP4_BI2_Pin GPIO_PIN_7
#define STEP4_BI2_GPIO_Port GPIOG
#define STEP4_BI1_Pin GPIO_PIN_8
#define STEP4_BI1_GPIO_Port GPIOG
#define STEP4_AI2_Pin GPIO_PIN_6
#define STEP4_AI2_GPIO_Port GPIOG
#define STEP4_AI1_Pin GPIO_PIN_5
#define STEP4_AI1_GPIO_Port GPIOG
#define STEP2_BI1_Pin GPIO_PIN_13
#define STEP2_BI1_GPIO_Port GPIOD
#define STEP2_BI2_Pin GPIO_PIN_12
#define STEP2_BI2_GPIO_Port GPIOD
#define STEP2_AI2_Pin GPIO_PIN_11
#define STEP2_AI2_GPIO_Port GPIOD
#define STEP2_AI1_Pin GPIO_PIN_10
#define STEP2_AI1_GPIO_Port GPIOD
#define STEP3_BI2_Pin GPIO_PIN_14
#define STEP3_BI2_GPIO_Port GPIOD
#define STEP3_BI1_Pin GPIO_PIN_15
#define STEP3_BI1_GPIO_Port GPIOD
#define STEP3_AI2_Pin GPIO_PIN_2
#define STEP3_AI2_GPIO_Port GPIOG
#define STEP3_AI1_Pin GPIO_PIN_3
#define STEP3_AI1_GPIO_Port GPIOG
#define STEP1_BI1_Pin GPIO_PIN_8
#define STEP1_BI1_GPIO_Port GPIOD
#define STEP1_BI2_Pin GPIO_PIN_15
#define STEP1_BI2_GPIO_Port GPIOB
#define STEP1_AI2_Pin GPIO_PIN_14
#define STEP1_AI2_GPIO_Port GPIOB
#define STEP1_AI1_Pin GPIO_PIN_13
#define STEP1_AI1_GPIO_Port GPIOB
#define BUTTON2_Pin GPIO_PIN_1
#define BUTTON2_GPIO_Port GPIOD
#define GPS_ONOFF_Pin GPIO_PIN_2
#define GPS_ONOFF_GPIO_Port GPIOD
#define GPS_RPFWRUP_Pin GPIO_PIN_3
#define GPS_RPFWRUP_GPIO_Port GPIOD
#define GPS_RESET_Pin GPIO_PIN_4
#define GPS_RESET_GPIO_Port GPIOD
#define SP1_NSS_Pin GPIO_PIN_6
#define SP1_NSS_GPIO_Port GPIOB

#define SPI_ENTITY_SIZE 108
#define SPI_TRANSFER_SIZE 120
#define SPI_DATA_SIZE 116


typedef struct
{
    uint32_t temperature;
    uint32_t compass_degree;
    uint32_t pressure;
    uint32_t altitude;
    uint8_t wheather_condition;

}SENSOR_DATA;

typedef struct
{
    uint16_t header;
    unsigned char data[SPI_DATA_SIZE];
    uint16_t checksum;

}SPI_TRANSFER_FORMAT;



typedef struct
{

    unsigned char gps_string[99];
    SENSOR_DATA sensor_data;

}ENVIRONMENT_DATA_FORMAT;

typedef struct
{
    uint32_t total_sequence_number;
    uint32_t current_sequence_number;

    unsigned char data[108];


}UPDATE_FILE_FORMAT;

typedef struct
{


    uint8_t garbage1[46];
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

    uint8_t garbage2[46];


}CONTROL_DATA_FORMAT;


/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

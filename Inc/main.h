/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CH11_Pin GPIO_PIN_0
#define CH11_GPIO_Port GPIOC
#define VREF_Pin GPIO_PIN_1
#define VREF_GPIO_Port GPIOC
#define CH12_Pin GPIO_PIN_2
#define CH12_GPIO_Port GPIOC
#define CH4_Pin GPIO_PIN_3
#define CH4_GPIO_Port GPIOA
#define CH5_Pin GPIO_PIN_4
#define CH5_GPIO_Port GPIOA
#define CH6_Pin GPIO_PIN_5
#define CH6_GPIO_Port GPIOA
#define CH7_Pin GPIO_PIN_6
#define CH7_GPIO_Port GPIOA
#define CH8_Pin GPIO_PIN_7
#define CH8_GPIO_Port GPIOA
#define CH9_Pin GPIO_PIN_0
#define CH9_GPIO_Port GPIOB
#define CH10_Pin GPIO_PIN_1
#define CH10_GPIO_Port GPIOB
#define USB_SENSE_Pin GPIO_PIN_15
#define USB_SENSE_GPIO_Port GPIOA
#define FTDI_RESET_Pin GPIO_PIN_5
#define FTDI_RESET_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

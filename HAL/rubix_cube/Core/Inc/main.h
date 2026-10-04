/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define step_m1_Pin GPIO_PIN_0
#define step_m1_GPIO_Port GPIOA
#define dir_m1_Pin GPIO_PIN_1
#define dir_m1_GPIO_Port GPIOA
#define step_m2_Pin GPIO_PIN_2
#define step_m2_GPIO_Port GPIOA
#define dir_m2_Pin GPIO_PIN_3
#define dir_m2_GPIO_Port GPIOA
#define step_m3_Pin GPIO_PIN_4
#define step_m3_GPIO_Port GPIOA
#define dir_m3_Pin GPIO_PIN_5
#define dir_m3_GPIO_Port GPIOA
#define step_m4_Pin GPIO_PIN_6
#define step_m4_GPIO_Port GPIOA
#define dir_m4_Pin GPIO_PIN_7
#define dir_m4_GPIO_Port GPIOA
#define step_m5_Pin GPIO_PIN_0
#define step_m5_GPIO_Port GPIOB
#define dir_m5_Pin GPIO_PIN_1
#define dir_m5_GPIO_Port GPIOB
#define step_m6_Pin GPIO_PIN_10
#define step_m6_GPIO_Port GPIOB
#define dir_m6_Pin GPIO_PIN_11
#define dir_m6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

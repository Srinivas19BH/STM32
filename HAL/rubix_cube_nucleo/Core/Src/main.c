/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
void delay_us(uint32_t us);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t FinalData[100];
uint8_t RxData[100];
uint8_t temp[1];

volatile uint8_t indx = 0;
volatile uint8_t msgReady = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void sendMove(const char *move)
{
    HAL_UART_Transmit(&huart2,
                      (uint8_t *)move,
                      strlen(move),
                      HAL_MAX_DELAY);
}
void clockwise(uint32_t rotation,
               GPIO_TypeDef *DIR_PORT, uint16_t DIR_PIN,
               GPIO_TypeDef *STEP_PORT, uint16_t STEP_PIN)
{
    HAL_GPIO_WritePin(DIR_PORT, DIR_PIN, GPIO_PIN_SET);

    uint32_t steps = rotation * 1600;

    for (uint32_t i = 0; i < steps; i++)
    {
    	HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, GPIO_PIN_SET);
    	delay_us(1000);

    	HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, GPIO_PIN_RESET);
    	delay_us(1000);
    }
}

void anticlockwise(uint32_t rotation,
                   GPIO_TypeDef *DIR_PORT, uint16_t DIR_PIN,
                   GPIO_TypeDef *STEP_PORT, uint16_t STEP_PIN)
{
    HAL_GPIO_WritePin(DIR_PORT, DIR_PIN, GPIO_PIN_RESET);

    uint32_t steps = rotation * 1600;

    for (uint32_t i = 0; i < steps; i++)
    {
    	HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, GPIO_PIN_SET);
    	delay_us(100);

    	HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, GPIO_PIN_RESET);
    	delay_us(100);
    }
}

uint32_t random_move(void)
{
    return (rand() % 18) + 1;
}

/* M1 = U: GPIOA */

void U(void)
{
    clockwise(1, GPIOA, m1_dir_Pin, GPIOA, m1_step_Pin);
    sendMove("U ");
}

void U2(void)
{
    clockwise(2, GPIOA, m1_dir_Pin, GPIOA, m1_step_Pin);
    sendMove("U2 ");
}

void U_INVERSE(void)
{
    anticlockwise(1, GPIOA, m1_dir_Pin, GPIOA, m1_step_Pin);
    sendMove("U' ");
}


void R(void)
{
    clockwise(1, GPIOA, m2_dir_Pin, GPIOA, m2_step_Pin);
    sendMove("R ");
}

void R2(void)
{
    clockwise(2, GPIOA, m2_dir_Pin, GPIOA, m2_step_Pin);
    sendMove("R2 ");
}

void R_INVERSE(void)
{
    anticlockwise(1, GPIOA, m2_dir_Pin, GPIOA, m2_step_Pin);
    sendMove("R' ");
}


void F(void)
{
    clockwise(1, GPIOC, m3_dir_Pin, GPIOC, m3_step_Pin);
    sendMove("F ");
}

void F2(void)
{
    clockwise(2, GPIOC, m3_dir_Pin, GPIOC, m3_step_Pin);
    sendMove("F2 ");
}

void F_INVERSE(void)
{
    anticlockwise(1, GPIOC, m3_dir_Pin, GPIOC, m3_step_Pin);
    sendMove("F' ");
}


void D(void)
{
    clockwise(1, GPIOB, m4_dir_Pin, GPIOB, m4_step_Pin);
    sendMove("D ");
}

void D2(void)
{
    clockwise(2, GPIOB, m4_dir_Pin, GPIOB, m4_step_Pin);
    sendMove("D2 ");
}

void D_INVERSE(void)
{
    anticlockwise(1, GPIOB, m4_dir_Pin, GPIOB, m4_step_Pin);
    sendMove("D' ");
}


void L(void)
{
    clockwise(1, GPIOB, m5_dir_Pin, GPIOB, m5_step_Pin);
    sendMove("L ");
}

void L2(void)
{
    clockwise(2, GPIOB, m5_dir_Pin, GPIOB, m5_step_Pin);
    sendMove("L2 ");
}

void L_INVERSE(void)
{
    anticlockwise(1, GPIOB, m5_dir_Pin, GPIOB, m5_step_Pin);
    sendMove("L' ");
}


void B(void)
{
    clockwise(1, GPIOB, m6_dir_Pin, GPIOB, m6_step_Pin);
    sendMove("B ");
}

void B2(void)
{
    clockwise(2, GPIOB, m6_dir_Pin, GPIOB, m6_step_Pin);
    sendMove("B2 ");
}

void B_INVERSE(void)
{
    anticlockwise(1, GPIOB, m6_dir_Pin, GPIOB, m6_step_Pin);
    sendMove("B' ");
}

void executeMoves(char *sequence)
{
    char *move = strtok(sequence, " \t\r\n");

    while (move != NULL)
    {
        if (strcmp(move, "U") == 0) U();
        else if (strcmp(move, "U2") == 0) U2();
        else if (strcmp(move, "U'") == 0) U_INVERSE();

        else if (strcmp(move, "R") == 0) R();
        else if (strcmp(move, "R2") == 0) R2();
        else if (strcmp(move, "R'") == 0) R_INVERSE();

        else if (strcmp(move, "F") == 0) F();
        else if (strcmp(move, "F2") == 0) F2();
        else if (strcmp(move, "F'") == 0) F_INVERSE();

        else if (strcmp(move, "D") == 0) D();
        else if (strcmp(move, "D2") == 0) D2();
        else if (strcmp(move, "D'") == 0) D_INVERSE();

        else if (strcmp(move, "L") == 0) L();
        else if (strcmp(move, "L2") == 0) L2();
        else if (strcmp(move, "L'") == 0) L_INVERSE();

        else if (strcmp(move, "B") == 0) B();
        else if (strcmp(move, "B2") == 0) B2();
        else if (strcmp(move, "B'") == 0) B_INVERSE();

        move = strtok(NULL, " \t\r\n");
    }
}
void DWT_Delay_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000U);

    while ((DWT->CYCCNT - start) < ticks);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  DWT_Delay_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, temp, 1);
  /* USER CODE END 2 */
  srand(HAL_GetTick());
  for (uint32_t i = 0; i < 20; i++)
  {
      uint32_t a = random_move();

      switch (a)
      {
          case 1:  U();          break;
          case 2:  U2();         break;
          case 3:  U_INVERSE();  break;

          case 4:  R();          break;
          case 5:  R2();         break;
          case 6:  R_INVERSE();  break;

          case 7:  F();          break;
          case 8:  F2();         break;
          case 9:  F_INVERSE();  break;

          case 10: D();          break;
          case 11: D2();         break;
          case 12: D_INVERSE();  break;

          case 13: L();          break;
          case 14: L2();         break;
          case 15: L_INVERSE();  break;

          case 16: B();          break;
          case 17: B2();         break;
          case 18: B_INVERSE();  break;

          default: break;
      }
  }
  HAL_UART_Transmit(&huart2,
                    (uint8_t *)"\r\n",
                    2,
                    HAL_MAX_DELAY);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
      if (msgReady == 1)
      {
          char moves[100];

          __disable_irq();
          strcpy(moves, (char *)FinalData);
          msgReady = 0;
          __enable_irq();

          executeMoves(moves);

          HAL_UART_Transmit(&huart2,
                            (uint8_t *)"\r\nDone\r\n",
                            8,
                            HAL_MAX_DELAY);
      }
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, m1_dir_Pin|m1_step_Pin|m2_dir_Pin|m2_step_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, m3_dir_Pin|m3_step_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, m4_dir_Pin|m4_step_Pin|m5_dir_Pin|m5_step_Pin
                          |m6_dir_Pin|m6_step_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : m1_dir_Pin m1_step_Pin m2_dir_Pin m2_step_Pin */
  GPIO_InitStruct.Pin = m1_dir_Pin|m1_step_Pin|m2_dir_Pin|m2_step_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : m3_dir_Pin m3_step_Pin */
  GPIO_InitStruct.Pin = m3_dir_Pin|m3_step_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : m4_dir_Pin m4_step_Pin m5_dir_Pin m5_step_Pin
                           m6_dir_Pin m6_step_Pin */
  GPIO_InitStruct.Pin = m4_dir_Pin|m4_step_Pin|m5_dir_Pin|m5_step_Pin
                          |m6_dir_Pin|m6_step_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (temp[0] == '\r' || temp[0] == '\n')
        {
            if (indx > 0)
            {
                memcpy(FinalData, RxData, indx);
                FinalData[indx] = '\0';

                indx = 0;
                msgReady = 1;
            }
        }
        else if (indx < sizeof(RxData) - 1)
        {
            RxData[indx++] = temp[0];
        }

        HAL_UART_Receive_IT(&huart2, temp, 1);
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#include <stdio.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define LED1_PORT			(GPIOA)
#define LED2_PORT			(GPIOA)
#define LED3_PORT			(GPIOC)
#define LED4_PORT			(GPIOC)

#define LED1_PIN			(GPIO_PIN_2)
#define LED2_PIN			(GPIO_PIN_1)
#define LED3_PIN			(GPIO_PIN_15)
#define LED4_PIN			(GPIO_PIN_14)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

void CAN1_FiterConfig(void);

void LedManage(uint8_t Copy_u8LedNum);
void ManageResponse(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  /* CAN Interrupt Enable*/
  if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
  {
	  Error_Handler();
  }

  CAN1_FiterConfig();

  /* Go to normal mode */
  HAL_CAN_Start(&hcan1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL13;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 4;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void CAN1_FiterConfig(void)
{
	CAN_FilterTypeDef Local_FilterConfig =
	{
			.FilterActivation = CAN_FILTER_ENABLE,
			.FilterBank = 0U,
			.FilterFIFOAssignment = CAN_RX_FIFO0,
			.FilterMaskIdHigh = 0U,
			.FilterMaskIdLow = 0U,
			.FilterMode = CAN_FILTERMODE_IDMASK,
			.FilterScale = CAN_FILTERSCALE_32BIT
	};

	if (HAL_CAN_ConfigFilter(&hcan1, &Local_FilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

//void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
//{
//	char Local_chTransmitMsg[50];
//
//	sprintf(Local_chTransmitMsg, "Message transmitted: MB0\r\n");
//
//	HAL_UART_Transmit(&huart2, (uint8_t *)Local_chTransmitMsg, strlen(Local_chTransmitMsg), HAL_MAX_DELAY);
//}
//
//void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
//{
//	char Local_chTransmitMsg[50];
//
//	sprintf(Local_chTransmitMsg, "Message transmitted: MB1\r\n");
//
//	HAL_UART_Transmit(&huart2, (uint8_t *)Local_chTransmitMsg, strlen(Local_chTransmitMsg), HAL_MAX_DELAY);
//}
//
//void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
//{
//	char Local_chTransmitMsg[50];
//
//	sprintf(Local_chTransmitMsg, "Message transmitted: MB2\r\n");
//
//	HAL_UART_Transmit(&huart2, (uint8_t *)Local_chTransmitMsg, strlen(Local_chTransmitMsg), HAL_MAX_DELAY);
//}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef Local_CanRxHdr;
	uint8_t Local_au8ReceivedData[8U];
	//char Local_chReceivedMsg[50];

	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &Local_CanRxHdr, (uint8_t *)&Local_au8ReceivedData) != HAL_OK)
	{
		Error_Handler();
	}
	else
	{
		/* Correctly received the frame */
		if ((Local_CanRxHdr.StdId == 0x65D) && (Local_CanRxHdr.RTR == CAN_RTR_DATA))
		{
			/* Our led managment frame */
			LedManage(Local_au8ReceivedData[0U]);

		}
		else if ((Local_CanRxHdr.StdId == 0x651) && (Local_CanRxHdr.RTR == CAN_RTR_REMOTE))
		{
			ManageResponse();
		}
	}

	//sprintf(Local_chReceivedMsg, "Message received: %s\r\n", (char*)&Local_au8ReceivedData);

	//HAL_UART_Transmit(&huart2, (uint8_t *)&Local_chReceivedMsg, strlen((char*)&Local_chReceivedMsg), HAL_MAX_DELAY);
}

void LedManage(uint8_t Copy_u8LedNum)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_RESET);

	switch (Copy_u8LedNum)
	{
	case 1: HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET); break;
	case 2: HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET); break;
	case 3: HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET); break;
	case 4: HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_SET); break;
	default: break;
	}
}

void ManageResponse(void)
{
	uint8_t Local_au8Response[8U] = {0xAA, 0xBB};

	CAN_TxHeaderTypeDef Local_CanTxHdr;
	uint32_t Local_u32Mailbox;

	Local_CanTxHdr.StdId = 0x651U;
	Local_CanTxHdr.IDE = CAN_ID_STD;
	Local_CanTxHdr.RTR = CAN_RTR_DATA;
	Local_CanTxHdr.DLC = 2U;

	if (HAL_CAN_AddTxMessage(&hcan1, &Local_CanTxHdr, (uint8_t *)&Local_au8Response, &Local_u32Mailbox) != HAL_OK)
	{
		Error_Handler();
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

#ifdef  USE_FULL_ASSERT
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

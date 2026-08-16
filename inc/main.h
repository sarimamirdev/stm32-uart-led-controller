#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
extern GPIO_InitTypeDef GPIO_InitStruct;

/* Private define ------------------------------------------------------------*/
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void Error_Handler(void);

#endif /* __MAIN_H */

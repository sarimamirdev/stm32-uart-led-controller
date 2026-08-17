#include "usart.h"

UART_HandleTypeDef huart1;

/**
 * @brief Initialize USART1
 *
 * Configuration:
 * - Baud Rate: 115200
 * - Data Bits: 8
 * - Stop Bits: 1
 * - Parity: None
 * - Mode: TX + RX
 * - Hardware Flow Control: None
 * - Oversampling: 16
 */
void USART1_Init(void)
{
    /* Enable USART1 peripheral clock */
    __HAL_RCC_USART1_CLK_ENABLE();

    huart1.Instance = USART1;

    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

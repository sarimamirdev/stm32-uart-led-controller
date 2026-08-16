#include "usart.h"

UART_HandleTypeDef huart1;

/**
 * @brief Initialize USART1
 * - Baud Rate: 115200
 * - 8 Data Bits, 1 Stop Bit, No Parity
 * - No Hardware Flow Control
 */
void USART1_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart1) != HAL_OK)
        Error_Handler();
}

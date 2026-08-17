#include "gpio.h"

/**
 * @brief Initialize GPIO pins
 *
 * Pin Configuration:
 * - PE6  : LED2 output (Active Low)
 * - PA9  : USART1 TX
 * - PA10 : USART1 RX
 */
void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Enable GPIO clocks */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* ========================================
     * LED2 - PE6
     * ======================================== */

    GPIO_InitStruct.Pin = LED2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(LED2_PORT, &GPIO_InitStruct);

    /* LED OFF by default */
    LED2_OFF();

    /* ========================================
     * USART1 TX - PA9
     * ======================================== */

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ========================================
     * USART1 RX - PA10
     * ======================================== */

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

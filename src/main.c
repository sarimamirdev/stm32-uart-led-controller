#include "main.h"
#include "gpio.h"
#include "usart.h"

char recBuf[20];

/**
 * @brief Redirect printf to USART1
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/**
 * @brief Redirect scanf from USART1
 */
int fgetc(FILE *f)
{
    uint8_t ch;

    HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);

    return ch;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    GPIO_Init();
    USART1_Init();

    printf("\r\n");
    printf("========================================\r\n");
    printf("  STM32 UART LED Controller\r\n");
    printf("========================================\r\n");
    printf("  Commands: 'open'  -> LED ON\r\n");
    printf("           'close' -> LED OFF\r\n");
    printf("========================================\r\n");
    printf("Waiting for command...\r\n\r\n");

    while (1)
    {
        memset(recBuf, 0, sizeof(recBuf));

        printf("Enter command: ");

        /*
         * Read a maximum of 19 characters.
         * The 20th byte is reserved for the null terminator.
         */
        scanf("%19s", recBuf);

        if (strcmp(recBuf, "open") == 0)
        {
            LED2_ON();

            printf(">>> LED2 is ON!\r\n\r\n");
        }
        else if (strcmp(recBuf, "close") == 0)
        {
            LED2_OFF();

            printf(">>> LED2 is OFF!\r\n\r\n");
        }
        else
        {
            printf(">>> ERROR: Please enter 'open' or 'close'!\r\n");
            printf(">>> You entered: %s\r\n\r\n", recBuf);
        }
    }
}

/**
 * @brief System Clock Configuration - 72MHz
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
    }
}

void HardFault_Handler(void)
{
    while (1)
    {
    }
}

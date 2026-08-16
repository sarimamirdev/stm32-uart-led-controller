/*----------------------------------------------------------------------------
 * STM32 Serial Port Redirection and LED Control System
 * 
 * Description: 
 *   This program implements serial port redirection on STM32F103VET6,
 *   enabling printf() and scanf() to work over UART. It receives
 *   commands ("open" / "close") via serial terminal and controls
 *   LED2 (PE6) accordingly.
 * 
 * Hardware:
 *   - STM32F103VET6 Microcontroller
 *   - LED2 connected to PE6 (Active Low: LOW = ON, HIGH = OFF)
 *   - USART1 for serial communication (PA9-TX, PA10-RX)
 * 
 * Communication Parameters:
 *   - Baud Rate: 115200
 *   - Data Bits: 8
 *   - Stop Bits: 1
 *   - Parity: None
 * 
 * Commands:
 *   - "open"  → LED2 ON, responds "LED2 is open!"
 *   - "close" → LED2 OFF, responds "LED2 is close!"
 *   - Other   → Error message: "Please enter open/close! input error!"
 *----------------------------------------------------------------------------*/

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 * GLOBAL VARIABLES
 *----------------------------------------------------------------------------*/
uint8_t recBuf[20];     // Buffer to store received serial data

/*----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *----------------------------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

/*----------------------------------------------------------------------------
 * SERIAL PORT REDIRECTION FUNCTIONS
 *----------------------------------------------------------------------------*/

/**
 * @brief Redirects printf() output to USART1
 * @param ch: Character to be sent
 * @param f: File pointer (unused)
 * @return The character sent
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/**
 * @brief Redirects scanf() input from USART1
 * @param f: File pointer (unused)
 * @return The character received
 */
int fgetc(FILE *f)
{
    uint8_t ch;
    HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
    return ch;
}

/*----------------------------------------------------------------------------
 * MAIN PROGRAM
 *----------------------------------------------------------------------------*/

int main(void)
{
    // --- HAL Initialization ---
    HAL_Init();
    
    // --- System Clock Configuration (72MHz via HSE + PLL) ---
    SystemClock_Config();
    
    // --- Initialize Peripherals ---
    MX_GPIO_Init();        // Initialize GPIO (PE6 for LED2)
    MX_USART1_UART_Init(); // Initialize USART1
    
    // --- Send Startup Message ---
    printf("\r\n");
    printf("========================================\r\n");
    printf("  STM32 Serial Port Redirection Demo\r\n");
    printf("========================================\r\n");
    printf("  Commands: 'open'  → LED ON\r\n");
    printf("           'close' → LED OFF\r\n");
    printf("========================================\r\n");
    printf("Waiting for command...\r\n\r\n");
    
    // --- Main Loop ---
    while (1)
    {
        memset(recBuf, 0, sizeof(recBuf));
        
        printf("Enter command: ");
        scanf("%s", recBuf);
        
        // --- Command Parsing ---
        if (strcmp((char *)recBuf, "open") == 0)
        {
            // Turn LED2 ON (Active Low: RESET = LOW = ON)
            HAL_GPIO_WritePin(GPIOE, LED2_Pin, GPIO_PIN_RESET);
            printf(">>> LED2 is open!\r\n\r\n");
        }
        else if (strcmp((char *)recBuf, "close") == 0)
        {
            // Turn LED2 OFF (Active Low: SET = HIGH = OFF)
            HAL_GPIO_WritePin(GPIOE, LED2_Pin, GPIO_PIN_SET);
            printf(">>> LED2 is close!\r\n\r\n");
        }
        else
        {
            printf(">>> ERROR: Please enter 'open' or 'close'!\r\n");
            printf(">>> You entered: %s\r\n\r\n", recBuf);
        }
    }
}

/*----------------------------------------------------------------------------
 * SYSTEM CLOCK CONFIGURATION
 * Configure system clock to run at 72MHz using HSE + PLL
 *----------------------------------------------------------------------------*/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;   // 8MHz * 9 = 72MHz
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;    // HCLK = 72MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;     // APB1 = 36MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;     // APB2 = 72MHz
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/*----------------------------------------------------------------------------
 * USART1 INITIALIZATION
 *----------------------------------------------------------------------------*/
static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
}

/*----------------------------------------------------------------------------
 * GPIO INITIALIZATION
 *----------------------------------------------------------------------------*/
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // --- Configure PE6 as Output (LED2) ---
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // --- Configure USART1 Pins (PA9: TX, PA10: RX) ---
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/*----------------------------------------------------------------------------
 * ERROR HANDLER
 *----------------------------------------------------------------------------*/
void Error_Handler(void)
{
    __disable_irq();
    while (1) { /* Wait forever */ }
}

void HardFault_Handler(void)
{
    while (1) { /* Handle hardware fault */ }
}

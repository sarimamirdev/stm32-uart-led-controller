#ifndef __USART_H
#define __USART_H

#include "stm32f1xx_hal.h"

/* UART Handle Declaration */
extern UART_HandleTypeDef huart1;

/* Function Prototypes */
void USART1_Init(void);

#endif /* __USART_H */

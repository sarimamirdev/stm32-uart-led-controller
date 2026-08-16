#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f1xx_hal.h"

/* LED2 Pin Definition - Active Low */
#define LED2_PIN        GPIO_PIN_6
#define LED2_PORT       GPIOE

/* LED Control Macros */
#define LED2_ON()       HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET)
#define LED2_OFF()      HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET)
#define LED2_TOGGLE()   HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN)

/* Function Prototype */
void GPIO_Init(void);

#endif /* __GPIO_H */

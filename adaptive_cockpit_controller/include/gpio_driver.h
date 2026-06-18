#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

void GPIO_Init(void);

void GPIO_SetSafeState(void);

void GPIO_SetCautionState(void);

void GPIO_SetWarningState(void);

void GPIO_SetCriticalState(void);

void GPIO_SetFailsafeState(void);

#endif
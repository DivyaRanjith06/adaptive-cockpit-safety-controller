#ifndef INTERRUPT_DRIVER_H
#define INTERRUPT_DRIVER_H

#include <stdbool.h>

void InterruptDriver_Init(void);

bool InterruptDriver_IsEmergencyTriggered(void);

void InterruptDriver_ClearEmergencyTrigger(void);

#endif
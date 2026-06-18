#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#include <stdbool.h>

void InterruptManager_Init(void);

void InterruptManager_Update(void);

bool InterruptManager_IsEmergencyActive(void);

#endif
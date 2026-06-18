#ifndef WATCHDOG_DRIVER_H
#define WATCHDOG_DRIVER_H

#include <stdint.h>

void WatchdogDriver_Init(uint32_t TimeoutMs);

void WatchdogDriver_Feed(void);

#endif
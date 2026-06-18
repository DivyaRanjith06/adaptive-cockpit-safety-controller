#include "hardware/watchdog.h"

#include "watchdog_driver.h"

void WatchdogDriver_Init(uint32_t TimeoutMs)
{
    watchdog_enable(TimeoutMs, true);
}

void WatchdogDriver_Feed(void)
{
    watchdog_update();
}
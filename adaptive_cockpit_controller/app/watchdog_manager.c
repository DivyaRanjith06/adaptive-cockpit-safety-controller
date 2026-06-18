#include "watchdog_manager.h"

#include "watchdog_driver.h"
#include "system_config.h"

void WatchdogManager_Init(void)
{
    WatchdogDriver_Init(WATCHDOG_TIMEOUT_MS);
}

void WatchdogManager_Update(void)
{
    WatchdogDriver_Feed();
}
#include "interrupt_manager.h"

#include "interrupt_driver.h"

static bool EmergencyActive = false;

void InterruptManager_Init(void)
{
    InterruptDriver_Init();

    EmergencyActive = false;
}

void InterruptManager_Update(void)
{
    if (InterruptDriver_IsEmergencyTriggered())
    {
        EmergencyActive = true;

        InterruptDriver_ClearEmergencyTrigger();
    }
}

bool InterruptManager_IsEmergencyActive(void)
{
    return EmergencyActive;
}
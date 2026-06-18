#include "state_machine.h"

#include "gpio_driver.h"
#include "risk_engine.h"

static SystemState_t CurrentState =
    SYSTEM_STATE_SAFE;

void StateMachine_Init(void)
{
    CurrentState = SYSTEM_STATE_SAFE;
}

void StateMachine_Update(void)
{
    CurrentState =
        RiskEngine_GetSystemState();

    switch (CurrentState)
    {
        case SYSTEM_STATE_SAFE:

            GPIO_SetSafeState();

            break;

        case SYSTEM_STATE_CAUTION:

            GPIO_SetCautionState();

            break;

        case SYSTEM_STATE_WARNING:

            GPIO_SetWarningState();

            break;

        case SYSTEM_STATE_CRITICAL:

            GPIO_SetCriticalState();

            break;

        case SYSTEM_STATE_FAILSAFE:

            GPIO_SetFailsafeState();

            break;

        default:

            GPIO_SetFailsafeState();

            break;
    }
}

SystemState_t StateMachine_GetCurrentState(void)
{
    return CurrentState;
}
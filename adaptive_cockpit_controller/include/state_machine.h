#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
    SYSTEM_STATE_SAFE = 0,

    SYSTEM_STATE_CAUTION,

    SYSTEM_STATE_WARNING,

    SYSTEM_STATE_CRITICAL,

    SYSTEM_STATE_FAILSAFE

} SystemState_t;

void StateMachine_Init(void);

void StateMachine_Update(void);

SystemState_t StateMachine_GetCurrentState(void);

#endif
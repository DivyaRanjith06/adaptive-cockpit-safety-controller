#include "risk_engine.h"

#include "system_config.h"

static uint8_t RiskScore = 0U;

static SystemState_t CurrentState =
    SYSTEM_STATE_SAFE;

void RiskEngine_Update(SensorData_t SensorData,
                       bool EmergencyOverride)
{
    RiskScore = 0U;

    /*
     * Emergency Override
     */

    if (EmergencyOverride == true)
    {
        CurrentState = SYSTEM_STATE_CRITICAL;

        RiskScore = 100U;

        return;
    }

    /*
     * Speed Contribution
     */

    if (SensorData.SpeedValue >
        HIGH_SENSOR_THRESHOLD)
    {
        RiskScore += 50U;
    }
    else if (SensorData.SpeedValue >
             MEDIUM_SENSOR_THRESHOLD)
    {
        RiskScore += 30U;
    }
    else if (SensorData.SpeedValue >
             LOW_SENSOR_THRESHOLD)
    {
        RiskScore += 10U;
    }
    else
    {
        RiskScore += 0U;
    }

    /*
     * Attention Contribution
     */

    if (SensorData.AttentionValue >
        HIGH_SENSOR_THRESHOLD)
    {
        RiskScore += 50U;
    }
    else if (SensorData.AttentionValue >
             MEDIUM_SENSOR_THRESHOLD)
    {
        RiskScore += 30U;
    }
    else if (SensorData.AttentionValue >
             LOW_SENSOR_THRESHOLD)
    {
        RiskScore += 10U;
    }
    else
    {
        RiskScore += 0U;
    }

    /*
     * State Decision
     */

    if (RiskScore >= HIGH_RISK_THRESHOLD)
    {
        CurrentState = SYSTEM_STATE_CRITICAL;
    }
    else if (RiskScore >= MEDIUM_RISK_THRESHOLD)
    {
        CurrentState = SYSTEM_STATE_WARNING;
    }
    else if (RiskScore >= LOW_RISK_THRESHOLD)
    {
        CurrentState = SYSTEM_STATE_CAUTION;
    }
    else
    {
        CurrentState = SYSTEM_STATE_SAFE;
    }
}

SystemState_t RiskEngine_GetSystemState(void)
{
    return CurrentState;
}

uint8_t RiskEngine_GetRiskScore(void)
{
    return RiskScore;
}
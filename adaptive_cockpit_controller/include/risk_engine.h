#ifndef RISK_ENGINE_H
#define RISK_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include "sensor_manager.h"
#include "state_machine.h"

void RiskEngine_Update(SensorData_t SensorData,
                       bool EmergencyOverride);

SystemState_t RiskEngine_GetSystemState(void);

uint8_t RiskEngine_GetRiskScore(void);

#endif
#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H

#include "sensor_manager.h"
#include "state_machine.h"
#include <stdint.h>
#include <stdbool.h>
void TelemetryService_Send(
    SensorData_t SensorData,
    uint8_t RiskScore,
    SystemState_t SystemState,
    bool EmergencyActive);

#endif
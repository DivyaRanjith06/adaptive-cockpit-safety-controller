#include <stdio.h>

#include "telemetry_service.h"

void TelemetryService_Send(
    SensorData_t SensorData,
    uint8_t RiskScore,
    SystemState_t SystemState,
    bool EmergencyActive)
{
    printf("%u,%u,%u,%u,%u\r\n",
           SensorData.SpeedValue,
           SensorData.AttentionValue,
           RiskScore,
           (uint8_t)SystemState,
           (uint8_t)EmergencyActive);
}
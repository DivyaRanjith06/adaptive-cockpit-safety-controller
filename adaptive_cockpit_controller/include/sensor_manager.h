#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <stdint.h>

typedef struct
{
    uint16_t SpeedValue;

    uint16_t AttentionValue;

} SensorData_t;

void SensorManager_Init(void);

void SensorManager_Update(void);

SensorData_t SensorManager_GetData(void);

#endif
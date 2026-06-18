#include "sensor_manager.h"

#include "adc_driver.h"

static SensorData_t SensorData;

void SensorManager_Init(void)
{
    ADC_Driver_Init();

    SensorData.SpeedValue = 0U;

    SensorData.AttentionValue = 0U;
}

void SensorManager_Update(void)
{
    SensorData.SpeedValue =
        ADC_ReadSpeedSensor();

    SensorData.AttentionValue =
        ADC_ReadAttentionSensor();
}

SensorData_t SensorManager_GetData(void)
{
    return SensorData;
}
#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>

void ADC_Driver_Init(void);

uint16_t ADC_ReadSpeedSensor(void);

uint16_t ADC_ReadAttentionSensor(void);

#endif
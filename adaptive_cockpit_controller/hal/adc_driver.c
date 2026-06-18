#include "hardware/adc.h"

#include "adc_driver.h"
#include "pin_config.h"

void ADC_Driver_Init(void)
{
    adc_init();

    adc_gpio_init(SPEED_SENSOR_GPIO);

    adc_gpio_init(ATTENTION_SENSOR_GPIO);
}

uint16_t ADC_ReadSpeedSensor(void)
{
    adc_select_input(SPEED_SENSOR_ADC_CHANNEL);

    return adc_read();
}

uint16_t ADC_ReadAttentionSensor(void)
{
    adc_select_input(ATTENTION_SENSOR_ADC_CHANNEL);

    return adc_read();
}
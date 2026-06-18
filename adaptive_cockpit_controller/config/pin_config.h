#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include <stdint.h>

/*
 * LED Outputs
 */

#define GREEN_LED_PIN             (16U)
#define YELLOW_LED_PIN            (17U)
#define RED_LED_PIN               (18U)

/*
 * ADC Inputs
 */

#define SPEED_SENSOR_ADC_CHANNEL        (0U)
#define ATTENTION_SENSOR_ADC_CHANNEL    (1U)

#define SPEED_SENSOR_GPIO              (26U)
#define ATTENTION_SENSOR_GPIO          (27U)

/*
 * Emergency Interrupt Button
 */

#define EMERGENCY_BUTTON_PIN           (15U)

#endif
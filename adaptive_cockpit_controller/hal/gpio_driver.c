#include "pico/stdlib.h"

#include "gpio_driver.h"
#include "pin_config.h"

void GPIO_Init(void)
{
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(YELLOW_LED_PIN);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
}

void GPIO_SetSafeState(void)
{
    gpio_put(GREEN_LED_PIN, 1U);
    gpio_put(YELLOW_LED_PIN, 0U);
    gpio_put(RED_LED_PIN, 0U);
}

void GPIO_SetCautionState(void)
{
    gpio_put(GREEN_LED_PIN, 0U);
    gpio_put(YELLOW_LED_PIN, 1U);
    gpio_put(RED_LED_PIN, 0U);
}

void GPIO_SetWarningState(void)
{
    static bool Toggle = false;

    Toggle = !Toggle;

    gpio_put(GREEN_LED_PIN, 0U);
    gpio_put(YELLOW_LED_PIN, Toggle);
    gpio_put(RED_LED_PIN, 0U);
}

void GPIO_SetCriticalState(void)
{
    gpio_put(GREEN_LED_PIN, 0U);
    gpio_put(YELLOW_LED_PIN, 0U);
    gpio_put(RED_LED_PIN, 1U);
}

void GPIO_SetFailsafeState(void)
{
    static bool Toggle = false;

    Toggle = !Toggle;

    gpio_put(GREEN_LED_PIN, 0U);
    gpio_put(YELLOW_LED_PIN, 0U);
    gpio_put(RED_LED_PIN, Toggle);
}
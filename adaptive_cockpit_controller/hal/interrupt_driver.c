#include "pico/stdlib.h"

#include "interrupt_driver.h"
#include "pin_config.h"

static volatile bool EmergencyTriggered = false;

static void GPIO_InterruptHandler(uint gpio,
                                  uint32_t events)
{
    if ((gpio == EMERGENCY_BUTTON_PIN) &&
        (events & GPIO_IRQ_EDGE_FALL))
    {
        EmergencyTriggered = true;
    }
}

void InterruptDriver_Init(void)
{
    gpio_init(EMERGENCY_BUTTON_PIN);

    gpio_set_dir(EMERGENCY_BUTTON_PIN, GPIO_IN);

    gpio_pull_up(EMERGENCY_BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(
        EMERGENCY_BUTTON_PIN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &GPIO_InterruptHandler);
}

bool InterruptDriver_IsEmergencyTriggered(void)
{
    return EmergencyTriggered;
}

void InterruptDriver_ClearEmergencyTrigger(void)
{
    EmergencyTriggered = false;
}
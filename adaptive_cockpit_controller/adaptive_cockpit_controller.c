#include "pico/stdlib.h"
#include "system_config.h"
#include "sensor_manager.h"
#include "risk_engine.h"
#include "state_machine.h"
#include "interrupt_manager.h"
#include "watchdog_manager.h"
#include "telemetry_service.h"
#include "gpio_driver.h"

int main(void)
{
    SensorData_t SensorData;

    bool EmergencyActive = false;

    stdio_init_all();

    sleep_ms(2000U);

    GPIO_Init();

    SensorManager_Init();

    InterruptManager_Init();

    WatchdogManager_Init();

    StateMachine_Init();

    while (true)
    {
        /*
         * Sensor Acquisition
         */

        SensorManager_Update();

        SensorData =
            SensorManager_GetData();

        /*
         * Emergency Interrupt Handling
         */

        InterruptManager_Update();

        EmergencyActive =
            InterruptManager_IsEmergencyActive();

        /*
         * Risk Assessment
         */

        RiskEngine_Update(
            SensorData,
            EmergencyActive);

        /*
         * FSM Output Update
         */

        StateMachine_Update();

        /*
         * UART Telemetry
         */

        TelemetryService_Send(
            SensorData,
            RiskEngine_GetRiskScore(),
            StateMachine_GetCurrentState(),
            EmergencyActive);

        /*
         * Watchdog Feed
         */

        WatchdogManager_Update();

        sleep_ms(TELEMETRY_INTERVAL_MS);
    }
}
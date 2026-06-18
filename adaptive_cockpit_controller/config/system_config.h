#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include <stdint.h>

/*
 * Risk Thresholds
 */

#define LOW_RISK_THRESHOLD         (30U)
#define MEDIUM_RISK_THRESHOLD      (60U)
#define HIGH_RISK_THRESHOLD        (80U)

/*
 * ADC Thresholds
 */

#define LOW_SENSOR_THRESHOLD       (1000U)
#define MEDIUM_SENSOR_THRESHOLD    (2000U)
#define HIGH_SENSOR_THRESHOLD      (3000U)

/*
 * Telemetry Timing
 */

#define TELEMETRY_INTERVAL_MS      (500U)

/*
 * Watchdog Timeout
 */

#define WATCHDOG_TIMEOUT_MS        (3000U)

#endif
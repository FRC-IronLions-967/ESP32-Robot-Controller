#include "BatteryMonitor.h"

const uint16_t team967::BatteryMonitor::FULL_VAL = (1<<12);

const double team967::BatteryMonitor::FULL_VOLTAGE = 12.0;

bool team967::BatteryMonitor::initialized = false;

double team967::BatteryMonitor::getBatteryVoltage() {
    if(!initialized) {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(ADC_CHANNEL_5, ADC_ATTEN_DB_11);
        initialized = true;
    }
    return (((double) adc1_get_raw(ADC_CHANNEL_5)) / ((double) FULL_VAL)) * FULL_VOLTAGE;
}
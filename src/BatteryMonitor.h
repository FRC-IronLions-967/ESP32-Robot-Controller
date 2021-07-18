#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <driver/adc.h>
#include <stdint.h>

namespace team967 {

    class BatteryMonitor {
        private:
            // what value will be read on the analog pin when the battery is full
            static const uint16_t FULL_VAL;
            // the voltage that FULL_VAL represents
            static const double FULL_VOLTAGE;
            // whether or not the adc has been initialized before
            static bool initialized;

        public:
            /**
             * Static member function that returns an estimate of the current battery voltage by reading the analog input pin tied to the battery
             * and dividing that value by FULL_VAL, then multiplying the result by FULL_VOLTAGE.
             * 
             * @param none
             * @return An estimate of the battery voltage as a double
             */
            static double getBatteryVoltage();

    };

}

#endif
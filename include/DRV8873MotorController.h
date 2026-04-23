/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-11-2026

This header provides a class for interfacing with the DRV8873 H-Bridge Motor Driver IC from Texas Instruments.  See TI documentation
for device specific details.

**************************************************************************************************************************************/

#ifndef TEAM967_DRV8873MOTORCONTROLLER_H
#define TEAM967_DRV8873MOTORCONTROLLER_H

#include <MotorController.h>

#include <stdint.h>

namespace team967 {

    /**
     * Class to interface with the DRV8873 H-Bridge Motor Driver IC from Texas Instruments.  This IC has several operating modes, but
     * this class uses the PWM mode (which is the device default).  Configuration and status monitoring are done via a SPI interface,
     * but motor power and inversion status are set via PWM over two pins.
     */
    class DRV8873MotorController : public MotorController {

        private:
            int pin0;
            int pin1;
            int channel;
            int frequency;
            int resolution;

            int currentAttachedPin;

        public:
            /**
             * Constructor to create a new DRV8873MotorController with the specified options.
             * 
             * @return A new DRV8873MotorController object
             */
            DRV8873MotorController(int pin0, int pin1, int channel, int frequency, int resolution);

            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            ~DRV8873MotorController();

            /**
             * Initialize the pins and timers.
             * 
             * @return nothing
             */
            void begin(void);

            /**
             * Function to set motor power.
             * 
             * @return nothing
             */
            void setPower(int32_t power);

    };

}

#endif
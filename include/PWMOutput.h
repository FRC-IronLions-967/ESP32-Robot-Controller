/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-17-2026

Last Updated: 4-17-2026

This header provides a class for generating a PWM output.

**************************************************************************************************************************************/

#ifndef TEAM967_PWMOUTPUT_H
#define TEAM967_PWMOUTPUT_H

#include <stdint.h>

namespace team967 {

    class PWMOutput {

        public:
            /**
             * Virtual destructor.
             * 
             * @return nothing
             */
            virtual ~PWMOutput() = 0;

            /**
             * Initialize the channels.
             */

            /**
             * Function to get the frequency in Hertz of the PWM channel.
             * 
             * @return frequency in Hertz as integer
             */
            virtual uint32_t getFreqHz() = 0;

            /**
             * Function to get the maximum value that can be set for the duty cycle.
             * 
             * @return maximum duty cycle for PWM channel
             */
            virtual uint32_t getMaxDuty() = 0;

            /**
             * Function to set the duty cycle for the PWM channel.
             * 
             * @return nothing
             */
            virtual void setDuty(uint32_t duty) = 0;

    };

}

#endif
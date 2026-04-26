/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-25-2026

Last Updated: 4-25-2026

This header provides a class for interfacing with the MCPWM module in the ESP32S3.

**************************************************************************************************************************************/

#ifndef TEAM967_MCPWMCHANNEL_T
#define TEAM967_MCPWMCHANNEL_T

#include <stdint.h>

namespace team967 {

    class MCPWMChannel {

        public:
            const int MCPWM_REFERENCE_FREQ = 80 * 1000 * 1000;

            int mcpwmId;
            int channel;
            int pin0;
            int pin1;
            int frequency;
            int resolution;

            /**
             * Constructor for abstract class.
             * 
             * @param mcpwmId MCPWM module number (0 or 1)
             * @param channel Timer channel number (0 to 2)
             * @param pin0 First pin for motor control
             * @param pin1 Second pin for motor control
             * @param frequency PWM frequency in Hertz
             * @param resolution Resolution of PWM in bits
             */
            MCPWMChannel(int mcpwmId, int channel, int pin0, int pin1, int frequency, int resolution);

            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            virtual ~MCPWMChannel() = 0;

            /**
             * Initialize the pins and timers.
             * 
             * @return nothing
             */
            virtual void begin(void) = 0;

            /**
             * Set the motor to run forward, using a given duty cycle.
             * 
             * @param duty Forward duty cycle
             * 
             * @return nothing
             */            
            virtual void forward(uint32_t duty) = 0;

            /**
             * Set the motor to run in reverse, using a given duty cycle.
             * 
             * @param duty Reverse duty cycle
             * 
             * @return nothing
             */
            virtual void reverse(uint32_t duty) = 0;

            /**
             * Set the motor to off and brake.
             * 
             * @return nothing
             */
            virtual void brake(void) = 0;

            /**
             * Set the motor to off and coast.
             * 
             * @return nothing
             */
            virtual void coast(void) = 0;

    };

}

#endif
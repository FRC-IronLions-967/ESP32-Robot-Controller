/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-25-2026

Last Updated: 4-25-2026

This header provides a class for interfacing with the MCPWM module in the ESP32S3 with legacy API.

**************************************************************************************************************************************/

#ifndef TEAM967_ESP32S3LEGACYMCPWMCHANNEL_H
#define TEAM967_ESP32S3LEGACYMCPWMCHANNEL_H

#include <stdint.h>

#include <MCPWMChannel.h>

#include <Arduino.h>
#include "driver/mcpwm.h"

namespace team967 {

    /**
     * Class to interface with the MCPWM module in the ESP32S3.
     */
    class ESP32S3LegacyMCPWMChannel : public MCPWMChannel {

        private:
            mcpwm_config_t pwmConfig;

            mcpwm_unit_t pwmUnit;
            mcpwm_io_signals_t channelA;
            mcpwm_io_signals_t channelB;
            mcpwm_timer_t timer;

            bool initDone = false;

        public:
            /**
             * Constructor to create a new MCPWMChannel with the specified options.
             * 
             * @return A new MCPWMChannel object
             */
            ESP32S3LegacyMCPWMChannel(int mcpwmId, int channel, int pin0, int pin1, int frequency, int resolution);

            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            ~ESP32S3LegacyMCPWMChannel();

            /**
             * Initialize the pins and timers.
             * 
             * @return nothing
             */
            void begin(void);

            /**
             * Set the motor to run forward, using a given duty cycle.
             * 
             * @param duty Forward duty cycle
             * 
             * @return nothing
             */            
            void forward(uint32_t duty);

            /**
             * Set the motor to run in reverse, using a given duty cycle.
             * 
             * @param duty Reverse duty cycle
             * 
             * @return nothing
             */
            void reverse(uint32_t duty);

            /**
             * Set the motor to off and brake.
             * 
             * @return nothing
             */
            void brake(void);

            /**
             * Set the motor to off and coast.
             * 
             * @return nothing
             */
            void coast(void);
    };

}

#endif
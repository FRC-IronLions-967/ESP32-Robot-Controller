/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-17-2026

Last Updated: 4-17-2026

This header provides a class for generating a PWM output on the ESP32 S3 board.

**************************************************************************************************************************************/

#ifndef TEAM967_ESP32S3PWMOUTPUT_H
#define TEAM967_ESP32S3PWMOUTPUT_H

#include <Arduino.h>

#include <PWMOutput.h>

namespace team967 {

    class ESP32S3PWMOutput : public PWMOutput {

        private:
            ledc_timer_config_t* timerConfig;
            ledc_channel_config_t* channelConfig;

        public:
            /**
             * Constructor to create a new ESP32S3PWMOutput object.
             * 
             * @param timerConfig Configuration for timer (can be shared betweeen PWM channels)
             * @param channelConfig Configuration for channel (unique to each PWM channel)
             * 
             * @return A new ESP32S3PWMOutput object
             */
            ESP32S3PWMOutput(ledc_timer_config_t* timerConfig, ledc_channel_config_t* channelConfig);

            /**
             * Destructor.
             * 
             * @return nothing
             */
            ~ESP32S3PWMOutput();



            /**
             * Function to get the frequency in Hertz of the PWM channel.
             * 
             * @return frequency in Hertz as integer
             */
            uint32_t getFreqHz() = 0;

            /**
             * Function to get the maximum value that can be set for the duty cycle.
             * 
             * @return maximum duty cycle for PWM channel
             */
            uint32_t getMaxDuty() = 0;

            /**
             * Function to set the duty cycle for the PWM channel.
             * 
             * @return nothing
             */
            void setDuty(uint32_t duty) = 0;

    };

}

#endif
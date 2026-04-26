// /**************************************************************************************************************************************

// Author(s): Nathan Stark

// Created: 4-25-2026

// Last Updated: 4-25-2026

// This header provides a class for interfacing with the MCPWM module in the ESP32S3.

// **************************************************************************************************************************************/

// #ifndef TEAM967_ESP32S3MCPWMCHANNEL_H
// #define TEAM967_ESP32S3MCPWMCHANNEL_H

// #include <stdint.h>

// #include <MCPWMChannel.h>

// #include <Arduino.h>
// #include "driver/mcpwm_prelude.h"

// namespace team967 {

//     /**
//      * Class to interface with the MCPWM module in the ESP32S3.
//      */
//     class ESP32S3MCPWMChannel : public MCPWMChannel {

//         private:
//             mcpwm_timer_config_t timer_config;
//             mcpwm_operator_config_t oper_config;
//             mcpwm_comparator_config_t comp_config;
//             mcpwm_generator_config_t gen0_config;
//             mcpwm_generator_config_t gen1_config;

//             mcpwm_timer_handle_t timer;
//             mcpwm_oper_handle_t oper;
//             mcpwm_cmpr_handle_t comp;
//             mcpwm_gen_handle_t gen0;
//             mcpwm_gen_handle_t gen1;

//             bool initDone = false;

//         public:
//             const int MCPWM_REFERENCE_FREQ = 80 * 1000 * 1000;

//             int mcpwmId;
//             int pin0;
//             int pin1;
//             int frequency;
//             int resolution;

//             /**
//              * Constructor to create a new MCPWMChannel with the specified options.
//              * 
//              * @return A new MCPWMChannel object
//              */
//             ESP32S3MCPWMChannel(int mcpwmId, int pin0, int pin1, int frequency, int resolution);

//             /**
//              * Virtual destructor for class.
//              * 
//              * @return nothing
//              */
//             ~ESP32S3MCPWMChannel();

//             /**
//              * Initialize the pins and timers.
//              * 
//              * @return nothing
//              */
//             void begin(void);

//             /**
//              * Set the motor to run forward, using a given duty cycle.
//              * 
//              * @param duty Forward duty cycle
//              * 
//              * @return nothing
//              */            
//             void forward(uint32_t duty);

//             /**
//              * Set the motor to run in reverse, using a given duty cycle.
//              * 
//              * @param duty Reverse duty cycle
//              * 
//              * @return nothing
//              */
//             void reverse(uint32_t duty);

//             /**
//              * Set the motor to off and brake.
//              * 
//              * @return nothing
//              */
//             void brake(void);

//             /**
//              * Set the motor to off and coast.
//              * 
//              * @return nothing
//              */
//             void coast(void);
//     };

// }

// #endif
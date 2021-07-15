/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 5-15-2021

Last Updated: 6-21-2021

This header provides a class that allows the ESP32 to interface with standard PWM motor controllers, such as the CTRE Victors and
Talons as well as REV Robotics Sparks and SparkMaxes.  It uses the ESP32 PWM libraries and allows for complete customization over
PWM frequency and timer resolution.

**************************************************************************************************************************************/

#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include "ExternalEncoder.h"
#include <stdint.h>

// default frequency for the PWM signal in Hz
#define DEFAULT_PWM_FREQ 167

// resolution of the PWM duty cycles in bits
#define DEFAULT_PWM_RES 8

namespace team967 {

    /**
     * Class that provides a way to interact with PWM motor controllers.  This class assumes that the controller accepts 1/4 duty cycle as neutral, 1/6 as full reverse, and 1/3 as 
     * full forward.  This include most CTRE Talons and Victors, as well as REV Sparks.  This has been tested with Victor 888's and 884's, but it is assumed that it would work with
     * other controllers as well.
     */
    class MotorController {

        private:
            int p;
            int freq;
            int res;
            int chan;

            int dutyCycleMin;
            int dutyCycleMax;

            bool inv;

            team967::Encoder* attachedEncoder;

        public:
            /**
             * Constructor to create a new MotorController with the specified options.
             * 
             * @param pin The pin to use as a signal output for the motor controller
             * @param channel The PWM channel on the ESP32 to use to generate the waveform, can be 0-15
             * @param frequency The frequency (in Hz) to be used for the waveform, default is 167 Hz
             * @param resolution The resolution (in bits) to use for PWM generation, default is 8, max is 16
             * @return A new MotorController object
             */
            MotorController(int pin, int channel, int frequency = DEFAULT_PWM_FREQ, int resolution = DEFAULT_PWM_RES);

            /**
             * Destructor for the motor controller object.  Detaches the signal pin from the PWM channel so they can both be reused.
             * 
             * @param none
             * @return nothing
             */
            ~MotorController();

            /**
             * Sets the inversion state of this object.
             * 
             * @param inverted Whether or not this object's output should be inverted
             * @return nothing
             */
            void setInverted(bool inverted);

            /**
             * Returns whether or not this object's output is inverted.
             * 
             * @param none
             * @return true if inverted, false otherwise
             */
            bool isInverted(void);

            /**
             * Begins PWM output using the channel and pin specified in the constructor.  PWM duty cycle is set to 1/4 by default.
             * 
             * @param none
             * @return nothing
             */
            void begin(void);

            /**
             * Sets the power output of the motor.  The values passed to this depend on the resolution values specified earlier.  For example, in 8 bit mode the acceptable range for
             * values passed to this function is -128 to 127.  For 16 bit mode they are -32768 to 32767.
             * 
             * @param power The power value to set the output to
             * @return nothing
             */
            void set(int16_t power);

            /**
             * Attaches an Encoder object to this motor controller for measuring position, speed, etc.
             * 
             * @param encoder A reference to the encoder object to attach
             * @return nothing
             */
            void attachEncoder(team967::Encoder& encoder);

            /**
             * Returns a reference to the Encoder attached to this object.
             * 
             * @
             */
            team967::Encoder& getEncoder(void);

    };

}

#endif
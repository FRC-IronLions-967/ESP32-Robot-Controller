/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-12-2021

Last Updated: 6-21-2021

This header provides a class that provides similar functionality to the MotorController class, but commands servos to absolute
positions instead.  Currently the class is rather limited, and only supports a range of motion of +-90° from the neutral position.
This will likely be changed to allow for more flexibility.  If you wish to run a servo in continuous mode, the PWM control is nearly
identical to the PWM control for a motor controller, so you can just use the MotorController class to do so.

**************************************************************************************************************************************/

#ifndef PWMSERVO_H
#define PWMSERVO_H

#include <Arduino.h>
#include "ExternalEncoder.h"
#include <stdint.h>

// default frequency for the PWM signal in Hz
#define DEFAULT_PWM_FREQ 167

// resolution of the PWM duty cycles in bits
#define DEFAULT_PWM_RES 16

namespace team967 {

    class PWMServo {
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
             * Constructor to create a new PWMServo object with the specified options.
             * 
             * @param pin The GPIO pin to use for PWM output, can be one of the constants in CustomBoardPinDefs.h
             * @param channel The PWM channel to be used, can be any value between 0-15
             * @param frequency Optional parameter if a servo uses a different frequency, default is 167 Hz which should work with most servos
             * @param resolution Optional parameter which specifies the resolution (in bits) to use with the PWM channel
             * @return A new PWMServo object
             */
            PWMServo(int pin, int channel, int frequency = DEFAULT_PWM_FREQ, int resolution = DEFAULT_PWM_RES);

            /**
             * Destructor, detaches the pin from the PWM channel so that both can be used by something else.
             * 
             * @param none
             * @return nothing
             */
            ~PWMServo();

            /**
             * Member function to set the inversion state of this PWMServo object.  An inverted PWMServo rotates the opposite way as a non-inverted
             * one to reach the same angle.
             * 
             * @param inverted Whether or not this object should be inverted
             * @return nothing
             */
            void setInverted(bool inverted);

            /**
             * Member function to get the current inversion state of a PWMServo object.
             * 
             * @param none
             * @return true if the object is inverted, false otherwise
             */
            bool isInverted(void);

            /**
             * Member function to attach to the PWM channel and begin neutral output.
             * 
             * @param none
             * @return nothing
             */
            void begin(void);

            /**
             * Member function to set the angle of the servo in degrees.  Allowable values are between -90° and 90°.
             * 
             * @param angle The angle in degrees to set to
             * @return nothing
             */
            void setAngleDegrees(int8_t angle);

            /**
             * Member function to attach an Encoder object to the PWM servo for position/velocity tracking.  Please note that this class does not
             * copy or modify the Encoder pointer, the user is responsible for deleting it.
             * 
             * @param encoder A pointer to the Encoder object to attach
             * @return nothing
             */
            void attachEncoder(team967::Encoder *encoder);

            /**
             * Member function to get a pointer to the attached encoder.
             * 
             * @param none
             * @return A pointer to the attached encoder, or nullptr if it does not exist
             */
            team967::Encoder* getEncoder(void);

    };

}

#endif
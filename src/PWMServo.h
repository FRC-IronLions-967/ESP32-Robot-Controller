/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-12-2021

Last Updated: 6-17-2021

This header provides a class that provides similar functionality to the MotorController class, but commands servos to absolute
positions instead.  Currently the class is rather limited, and only supports a range of motion of +-90° from the neutral position.
This will likely be changed to allow for more flexibility.  If you wish to run a servo in continuous mode, the PWM control is nearly
identical to the PWM control for a motor controller, so you can just use the MotorController class to do so.

**************************************************************************************************************************************/

#ifndef PWMSERVO_H
#define PWMSERVO_H

#include <Arduino.h>
#include <stdint.h>

// default frequency for the PWM signal in Hz
#define DEFAULT_PWM_FREQ 167

// resolution of the PWM duty cycles in bits
#define DEFAULT_PWM_RES 16

class PWMServo {
    private:
        int p;
        int freq;
        int res;
        int chan;

        int dutyCycleMin;
        int dutyCycleMax;

        bool inv;

    public:
        PWMServo(int pin, int channel, int frequency = DEFAULT_PWM_FREQ, int resolution = DEFAULT_PWM_RES);
        ~PWMServo();
        void setInverted(bool inverted);
        bool isInverted(void);
        void begin(void);
        void setAngleDegrees(int8_t angle);

};

#endif
/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 5-15-2021

Last Updated: 6-17-2021

This header provides a class that allows the ESP32 to interface with standard PWM motor controllers, such as the CTRE Victors and
Talons as well as REV Robotics Sparks and SparkMaxes.  It uses the ESP32 PWM libraries and allows for complete customization over
PWM frequency and timer resolution.

**************************************************************************************************************************************/

#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include <stdint.h>

// default frequency for the PWM signal in Hz
#define DEFAULT_PWM_FREQ 167

// resolution of the PWM duty cycles in bits
#define DEFAULT_PWM_RES 8

class MotorController {

    private:
        int p;
        int freq;
        int res;
        int chan;

        int dutyCycleMin;
        int dutyCycleMax;

        bool inv;

    public:
        MotorController(int pin, int channel, int frequency = DEFAULT_PWM_FREQ, int resolution = DEFAULT_PWM_RES);
        ~MotorController();
        void setInverted(bool inverted);
        bool isInverted(void);
        void begin(void);
        void set(int16_t power);

};


#endif
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
        void setInverted(bool inverted);
        bool isInverted(void);
        void begin(void);
        void setAngleDegrees(int8_t angle);

};

#endif
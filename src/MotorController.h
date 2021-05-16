#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

// default frequency for the PWM signal in Hz
#define DEFAULT_PWM_FREQ 167

// resolution of the PWM duty cycles in bits
#define DEFAULT_PWM_RES 16

class MotorController {

private:
    int p;
    int freq;
    int res;
    int chan;

    int dutyCycleMin;
    int dutyCycleMax;

public:
    MotorController(int pin, int channel, int frequency = DEFAULT_PWM_FREQ, int resolution = DEFAULT_PWM_RES);
    void begin(void);
    void set(int16_t power);

};


#endif
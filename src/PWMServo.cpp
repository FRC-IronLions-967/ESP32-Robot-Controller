/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-12-2021

Last Updated: 6-19-2021

This file provides the definitions of the class methods defined in PWMServo.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include "PWMServo.h"

PWMServo::PWMServo(int pin, int channel, int frequency, int resolution): p(pin), chan(channel), freq(frequency), res(resolution) {
    // maximum supported resolution is 16 bits
    if(resolution > 16) resolution = 16;

    dutyCycleMin = ((1<<res) / 6);
    dutyCycleMax = ((1<<res) / 3);

    inv = false;
}

PWMServo::~PWMServo() {
    ledcDetachPin(p);
}

void PWMServo::setInverted(bool inverted) {
    inv = inverted;
}

bool PWMServo::isInverted() {
    return inv;
}

void PWMServo::begin() {
    pinMode(p, OUTPUT);

    // initialize the PWM channel used for the motor controller
    // uses LED PWM, but these seem to generate the correct waveforms so it should be fine
    ledcSetup(chan, freq, res);
    ledcAttachPin(p, chan);
}

void PWMServo::setAngleDegrees(int8_t angle) {
    if(angle > 90) angle = 90;
    if(angle < -90) angle = -90;

    // the neutral duty cycle is 1/4 of the full duty cycle, which is why the - 2 is here
    uint16_t dutyCycle = (1<<(res - 2));

    if(!inv) {
        dutyCycle += angle * (dutyCycleMax - dutyCycleMin) / 90;
    } else {
        dutyCycle -= angle * (dutyCycleMax - dutyCycleMin) / 90;
    }

    // I don't think we can exceed these bounds, but check just to be safe
    if(dutyCycle > dutyCycleMax) dutyCycle = dutyCycleMax;
    if(dutyCycle < dutyCycleMin) dutyCycle = dutyCycleMin;

    ledcWrite(chan, dutyCycle);
}

void PWMServo::attachEncoder(RotaryEncoder& encoder) {
    rotaryEncoder = &encoder;
}

RotaryEncoder& PWMServo::getEncoder() {
    return *rotaryEncoder;
}
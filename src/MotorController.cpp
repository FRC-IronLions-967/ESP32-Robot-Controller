#include "include/MotorController.h"

MotorController::MotorController(int pin, int channel, int frequency, int resolution): p(pin), chan(channel), freq(frequency), res(resolution) {
    // maximum supported resolution is 16 bits
    if(resolution > 16) resolution = 16;

    dutyCycleMin = ((1<<res) / 6);
    dutyCycleMax = ((1<<res) / 3);
}

void MotorController::begin() {
    pinMode(p, OUTPUT);

    // initialize the PWM channel used for the motor controller
    // uses LED PWM, but these seem to generate the correct waveforms so it should be fine
    ledcSetup(chan, freq, res);
    ledcAttachPin(p, chan);
}

void MotorController::set(int16_t power) {
    // the neutral duty cycle is 1/4 of the full duty cycle, which is why the - 2 is here
    uint16_t dutyCycle = (1<<(res - 2));

    int16_t divisor = (1<<(sizeof(power) * 8)) / (dutyCycleMax - dutyCycleMin);

    dutyCycle += power / divisor;

    // I don't think we can exceed these bounds, but check just to be safe
    if(dutyCycle > dutyCycleMax) dutyCycle = dutyCycleMax;
    if(dutyCycle < dutyCycleMin) dutyCycle = dutyCycleMin;

    ledcWrite(chan, dutyCycle);
}
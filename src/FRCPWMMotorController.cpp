/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 5-15-2021

Last Updated: 4-11-2026

This file provides the definitions of the class methods declared in FRCPWMMotorController.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include <FRCPWMMotorController.h>

team967::FRCPWMMotorController::FRCPWMMotorController(int pin, int channel, int frequency, int resolution) : 
                                                        MotorController(MOTOR_REVERSE | MOTOR_INVERT | MOTOR_COAST, (1 << resolution) - 1, -((1 << resolution) - 1), false, MOTOR_COAST),
                                                        p(pin), chan(channel), freq(frequency), res(resolution) {
    
    // maximum supported resolution is 16 bits
    if(res > 16) res = 16;

    dutyCycleMin = ((1<<res) / 6);
    dutyCycleMax = ((1<<res) / 3);

    attachedEncoder = nullptr;
}

team967::FRCPWMMotorController::~FRCPWMMotorController() {
    ledcDetachPin(p);
}

void team967::FRCPWMMotorController::begin() {
    pinMode(p, OUTPUT);

    // initialize the PWM channel used for the motor controller
    // uses LED PWM, but these seem to generate the correct waveforms so it should be fine
    ledcSetup(chan, freq, res);
    ledcAttachPin(p, chan);
}

void team967::FRCPWMMotorController::setPower(int32_t power) {
   // the neutral duty cycle is 1/4 of the full duty cycle, which is why the - 2 is here
    uint16_t dutyCycle = (1<<(res - 2));

    int16_t divisor = (1<<res) / (dutyCycleMax - dutyCycleMin);

    if(!inv) {
        dutyCycle += power / divisor;
    } else {
        dutyCycle -= power / divisor;
    }

    // I don't think we can exceed these bounds, but check just to be safe
    if(dutyCycle > dutyCycleMax) dutyCycle = dutyCycleMax;
    if(dutyCycle < dutyCycleMin) dutyCycle = dutyCycleMin;

    ledcWrite(chan, dutyCycle);
}

void team967::FRCPWMMotorController::attachEncoder(team967::Encoder *encoder) {
    attachedEncoder = encoder;
}

team967::Encoder* team967::FRCPWMMotorController::getEncoder() {
    return attachedEncoder;
}
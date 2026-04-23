/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-12-2026

Implementation of class in DRV8873MotorController.h

**************************************************************************************************************************************/

#include <DRV8873MotorController.h>

#include <Arduino.h>

team967::DRV8873MotorController::DRV8873MotorController(int pin0, int pin1, int channel, int frequency, int resolution) : 
                                                            MotorController(MOTOR_REVERSE | MOTOR_INVERT | MOTOR_COAST, (1 << resolution) - 1, -((1 << resolution) - 1), false, MOTOR_COAST),
                                                            pin0(pin0), pin1(pin1), channel(channel), frequency(frequency), resolution(resolution)
{
    currentAttachedPin = -1;
}

team967::DRV8873MotorController::~DRV8873MotorController() {

}

void team967::DRV8873MotorController::begin() {
    pinMode(pin0, OUTPUT);
    pinMode(pin1, OUTPUT);

    digitalWrite(pin0, HIGH);
    digitalWrite(pin1, HIGH);

    ledcSetup(channel, frequency, resolution);

    Serial.print("Resolution: ");
    Serial.println(resolution);
    Serial.print("Channel: ");
    Serial.println(channel);
    Serial.print("Frequency: ");
    Serial.println(frequency);
    Serial.print("Maximum power: ");
    Serial.println(maximumPower);
    Serial.print("Minimum power: ");
    Serial.println(minimumPower);
}

void team967::DRV8873MotorController::setPower(int32_t power) {
    // clamp input
    if(power > maximumPower) power = maximumPower;
    if(power < minimumPower) power = minimumPower;

    // apply inversion
    if(inverted) power = -power;
        
    if(power < 0) {
        // initialize the PWM channel used for the motor controller
        // uses LED PWM, but these seem to generate the correct waveforms
        if(currentAttachedPin == 1) {
            ledcDetachPin(pin1); // just for safety
            pinMode(pin1, OUTPUT);
            ledcAttachPin(pin0, channel);
            currentAttachedPin = 0;
        }

        digitalWrite(pin1, HIGH);
        ledcWrite(pin0, -power);
    } else if(power > 0) {
        // initialize the PWM channel used for the motor controller
        // uses LED PWM, but these seem to generate the correct waveforms
        if(currentAttachedPin == 0) {
            ledcDetachPin(pin0); // just for safety
            pinMode(pin0, OUTPUT);
            ledcAttachPin(pin1, channel);
            currentAttachedPin = 1;
        }

        digitalWrite(pin0, HIGH);
        ledcWrite(pin1, power);
    } else {
        // return the motor controller to idle state (power is 0 in this case)
        if(currentAttachedPin == 0) {
            ledcDetachPin(pin0);
            pinMode(pin0, OUTPUT);
        }
        if(currentAttachedPin == 1) {
            ledcDetachPin(pin1);
            pinMode(pin1, OUTPUT);
        }

        currentAttachedPin = -1;

        digitalWrite(pin0, HIGH);
        digitalWrite(pin1, HIGH);
    }
}
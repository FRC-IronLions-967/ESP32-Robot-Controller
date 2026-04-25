/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-12-2026

Implementation of class in DRV8873MotorController.h

**************************************************************************************************************************************/

#include <DRV8873MotorController.h>

#include <Arduino.h>
#include "driver/mcpwm.h"

team967::DRV8873MotorController::DRV8873MotorController(int pin0, int pin1, int frequency, int resolution) : 
                                                            MotorController(MOTOR_REVERSE | MOTOR_INVERT | MOTOR_BRAKE | MOTOR_COAST, (1 << resolution) - 1, -((1 << resolution) - 1), false, MOTOR_COAST),
                                                            pin0(pin0), pin1(pin1), frequency(frequency), resolution(resolution)
{

}

team967::DRV8873MotorController::~DRV8873MotorController() {

}

void team967::DRV8873MotorController::begin() {
    mcpwm_config_t config;

    pinMode(pin0, OUTPUT);
    pinMode(pin1, OUTPUT);

    digitalWrite(pin0, HIGH);
    digitalWrite(pin1, HIGH);

    Serial.print("Resolution: ");
    Serial.println(resolution);
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
        digitalWrite(pin1, HIGH);
    } else if(power > 0) {
        digitalWrite(pin0, HIGH);
    } else {
        digitalWrite(pin0, HIGH);
        digitalWrite(pin1, HIGH);
    }
}
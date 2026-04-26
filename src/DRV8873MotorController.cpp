/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-12-2026

Implementation of class in DRV8873MotorController.h

**************************************************************************************************************************************/

#include <DRV8873MotorController.h>

team967::DRV8873MotorController::DRV8873MotorController(MCPWMChannel* pwmChannel) : 
                                                            pwmChannel(pwmChannel),
                                                            MotorController(MOTOR_REVERSE | MOTOR_INVERT | MOTOR_BRAKE | MOTOR_COAST, (1 << pwmChannel->resolution) - 1, -((1 << pwmChannel->resolution) - 1), false, MOTOR_COAST)
                                                            
{
    
}

team967::DRV8873MotorController::~DRV8873MotorController() {

}

void team967::DRV8873MotorController::begin() {
    pwmChannel->begin();
}

void team967::DRV8873MotorController::setPower(int32_t power) {
    // clamp input
    if(power > maximumPower) power = maximumPower;
    if(power < minimumPower) power = minimumPower;

    // apply inversion
    if(inverted) power = -power;
        
    if(power < 0) {
        pwmChannel->reverse(std::abs(power));
    } else if(power > 0) {
        pwmChannel->forward(power);
    } else {
        if(coastBrakeMode == MOTOR_BRAKE) {
            pwmChannel->brake();
        } else {
            pwmChannel->coast();
        }
    }
}
#include <MotorController.h>

team967::MotorController::MotorController(uint32_t features, int32_t maximumPower, int32_t minimumPower, bool inverted, uint32_t coastBrakeMode) : features(features), maximumPower(maximumPower), minimumPower(minimumPower), inverted(inverted), coastBrakeMode(coastBrakeMode) {
    
}

team967::MotorController::~MotorController() {

}

bool team967::MotorController::supportsFeatures(uint32_t featureMask) {
    return ((featureMask & features) == featureMask);
}

int32_t team967::MotorController::MotorController::getMaximumMotorPower(void) {
    return maximumPower;
}

int32_t team967::MotorController::MotorController::getMinimumMotorPower(void) {
    return minimumPower;
}

void team967::MotorController::setInverted(bool inverted) {
    inverted = inverted;
}

bool team967::MotorController::isInverted(void) {
    return inverted;
}

void team967::MotorController::setCoastBrakeMode(uint32_t mode) {
    // input sanitization since we are reusing some constants
    if(mode != MOTOR_BRAKE && mode != MOTOR_COAST) return;

    coastBrakeMode = mode;
}

uint32_t team967::MotorController::getCoastBrakeMode(void) {
    return coastBrakeMode;
}
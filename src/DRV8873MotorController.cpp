/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-12-2026

Implementation of class in DRV8873MotorController.h

**************************************************************************************************************************************/

#include <DRV8873MotorController.h>

team967::DRV8873MotorController::DRV8873MotorController(MCPWMChannel* pwmChannel, SPIMaster* spi) : 
                                                            pwmChannel(pwmChannel),
                                                            spi(spi),
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

bool team967::DRV8873MotorController::readRegister(uint8_t addr, uint8_t* readData) {
    uint8_t txBuff[2];
    uint8_t rxBuff[2];

    // read command, don't care about data byte (index 1)
    // byte 0 has the following structure:
    // 7  6  5  4  3  2  1  0
    // 0  W0 A4 A3 A2 A1 A0 X
    // W0 is an active low write signal, A4:A0 are the register address, X is a don't care
    txBuff[0] = (addr & 0x1F) << 1;
    txBuff[0] |= 0x40;
    // This byte has the write data, which is irrelevant in this case
    txBuff[1] = 0x00;

    if(spi->writeAndRead(txBuff, rxBuff, 2) == 0) return false;

    *readData = rxBuff[1];

    return true;
}

bool team967::DRV8873MotorController::writeRegister(uint8_t addr, uint8_t writeData, uint8_t* readData) {
    uint8_t txBuff[2];
    uint8_t rxBuff[2];

    // read command, don't care about data byte (index 1)
    // byte 0 has the following structure:
    // 7  6  5  4  3  2  1  0
    // 0  W0 A4 A3 A2 A1 A0 X
    // W0 is an active low write signal, A4:A0 are the register address, X is a don't care
    txBuff[0] = (addr & 0x1F) << 1;
    // This byte has the write data
    txBuff[1] = writeData;

    if(spi->writeAndRead(txBuff, rxBuff, 2) == 0) return false;

    if(readData != nullptr) *readData = rxBuff[1];

    return true;
}

bool team967::DRV8873MotorController::faultOccurred(void) {
    uint8_t reg;

    if(!readRegister(FAULT_REG_ADDR, &reg)) return true; // we can't access SPI, so flag that something happened

    return (reg & 0x40);
}

bool team967::DRV8873MotorController::checkFault(uint8_t fault) {
    uint8_t reg;

    if(!readRegister(FAULT_REG_ADDR, &reg)) return false; // we can't access SPI, but this can't confirm a specific fault

    return (reg & fault);
}

bool team967::DRV8873MotorController::checkDiag(uint8_t diag) {
    uint8_t reg;

    if(!readRegister(DIAG_REG_ADDR, &reg)) return false;

    return (reg & diag);
}
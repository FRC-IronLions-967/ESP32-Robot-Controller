/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-11-2026

This header provides a class for interfacing with the DRV8873 H-Bridge Motor Driver IC from Texas Instruments.  See TI documentation
for device specific details.

**************************************************************************************************************************************/

#ifndef TEAM967_DRV8873MOTORCONTROLLER_H
#define TEAM967_DRV8873MOTORCONTROLLER_H

#include <MotorController.h>
#include <MCPWMChannel.h>
#include <SPIMaster.h>

#include <stdint.h>

#include <Arduino.h>

namespace team967 {

    /**
     * Class to interface with the DRV8873 H-Bridge Motor Driver IC from Texas Instruments.  This IC has several operating modes, but
     * this class uses the PWM mode (which is the device default).  Configuration and status monitoring are done via a SPI interface,
     * but motor power and inversion status are set via PWM over two pins.
     */
    class DRV8873MotorController : public MotorController {

        private:
            MCPWMChannel* pwmChannel;
            SPIMaster* spi;

        public:
            /**
             * Constants for SPI register addresses
             */
            const uint8_t FAULT_REG_ADDR = 0x00;
            const uint8_t DIAG_REG_ADDR  = 0x01;
            const uint8_t IC1_REG_ADDR   = 0x02;
            const uint8_t IC2_REG_ADDR   = 0x03;
            const uint8_t IC3_REG_ADDR   = 0x04;
            const uint8_t IC4_REG_ADDR   = 0x05;

            /**
             * Constants defining fault conditions in status register
             */
            const uint8_t FAULT_OTW  = 0x20;
            const uint8_t FAULT_UVLO = 0x10;
            const uint8_t FAULT_CPUV = 0x08;
            const uint8_t FAULT_OCP  = 0x04;
            const uint8_t FAULT_TSD  = 0x02;
            const uint8_t FAULT_OLD  = 0x01;

            /**
             * Constants defining some diagnostic flags for different faults
             */
            const uint8_t DIAG_OL1    = 0x80;
            const uint8_t DIAG_OL2    = 0x40;
            const uint8_t DIAG_ITRIP1 = 0x20;
            const uint8_t DIAG_ITRIP2 = 0x10;
            const uint8_t DIAG_OCP_H1 = 0x08;
            const uint8_t DIAG_OCP_L1 = 0x04;
            const uint8_t DIAG_OCP_H2 = 0x02;
            const uint8_t DIAG_OCP_L2 = 0x01;

            /**
             * Constructor to create a new DRV8873MotorController with the specified options.
             * 
             * @return A new DRV8873MotorController object
             */
            DRV8873MotorController(MCPWMChannel* pwmChannel, SPIMaster* spi);

            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            ~DRV8873MotorController();

            /**
             * Initialize the pins and timers.
             * 
             * @return nothing
             */
            void begin(void);

            /**
             * Function to set motor power.
             * 
             * @param power motor power (will be constrained within motor power bounds)
             * 
             * @return nothing
             */
            void setPower(int32_t power);

            /**
             * Read a register back via the SPI bus.
             * 
             * @param addr Address of register
             * @param readData Pointer to byte to place register into
             * 
             * @return true if successful, false otherwise
             */
            bool readRegister(uint8_t addr, uint8_t* readData);

            /**
             * Write a register via the SPI bus.
             * 
             * @param addr Address of register
             * @param writeData Data to write to the register
             * @param readData Pointer to byte to place read value into
             * 
             * @return true if successful, false otherwise
             */
            bool writeRegister(uint8_t addr, uint8_t writeData, uint8_t* readData);

            /**
             * Check if a fault has occurred on the motor controller.
             * 
             * @return true if fault, false otherwise
             */
            bool faultOccurred(void);

            /**
             * Check if a specific set of faults has occurred.  This will check the logical AND of the faults.
             * 
             * @param fault Fault flags to check (OR together for multiple)
             * 
             * @return true if fault(s) have occurred, false otherwise
             */
            bool checkFault(uint8_t fault);

            /**
             * Check if a specific diagnostic condition has occurred.
             * 
             * @param diag Diagnostic flags to check (OR together for multiple)
             * 
             * @return true if diagnostic condition has occurred, false otherwise
             */
            bool checkDiag(uint8_t diag);


    };

}

#endif
/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-11-2026

Last Updated: 4-11-2026

This header provides a base class for motor controllers to be derived from.  This can include both the old FRC style controllers
(Talons, Victors, Sparks) or the TI 8873 controllers used on the latest board revision.  This allows a unified interface to both types.

**************************************************************************************************************************************/

#ifndef TEAM967_MOTORCONTROLLER_H
#define TEAM967_MOTORCONTROLLER_H

#include <stdint.h>

namespace team967 {

    /**
     * Base class for motor controllers to be derived from.  This can include both the old FRC style controllers
     * (Talons, Victors, Sparks) or the TI 8873 controllers used on the latest board revision.  This allows a
     * unified interface to both types.
     */
    class MotorController {

        private:
            uint32_t features;

            int32_t maximumPower;
            int32_t minimumPower;

            bool inverted;

            uint32_t coastBrakeMode;

        public:
            /**
             * Constructor to create a new MotorController with the specified options.
             * 
             * @return A new MotorController object
             */
            MotorController(uint32_t features, int32_t maximumPower, int32_t minimumPower, bool inverted, uint32_t coastBrakeMode);

            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            ~MotorController();

            /**
             * Bit masks for the various potential features a MotorController might support.
             */
            const uint32_t MOTOR_REVERSE = 0x1;
            const uint32_t MOTOR_COAST   = 0x2;
            const uint32_t MOTOR_BRAKE   = 0x4;
            const uint32_t MOTOR_INVERT  = 0x8;

            /**
             * Function to check if the motor controller supports one or more features.
             * 
             * @param featureMask Bitmask of features to check
             * @return true if all queried features are supported, false otherwise
             */
            virtual bool supportsFeatures(uint32_t featureMask);

            /**
             * Function to get the maximum supported motor power.  For example, some controllers may take an 8 bit integer,
             * while others may take 16 bits.
             * 
             * @return Maximum supported motor power
             */
            virtual int32_t getMaximumMotorPower(void);

            /**
             * Function to get the minimum supported motor power.  For example, some controllers may take an 8 bit integer,
             * while others may take 16 bits.
             * 
             * @return Minimum supported motor power
             */

            virtual int32_t getMinimumMotorPower(void);

            /**
             * Function to invert the MotorController.  Depending on the underlying implementation, this may invert in hardware
             * (modifying the controller settings, or in software).
             * 
             * @param inverted Whether the motor should be inverted (true) or uninverted (false)
             * @return nothing
             */
            virtual void setInverted(bool inverted);

            /**
             * Function to check the current inversion status.
             * 
             * @return true if inverted, false otherwise
             */
            virtual bool isInverted(void);

            /**
             * Function to put the MotorController into coast or brake mode.  This may not be supported by every controller
             * 
             * @param mode mode to put controller in (MOTOR_COAST or MOTOR_BRAKE)
             * @return nothing
             */
            virtual void setCoastBrakeMode(uint32_t mode);

            /**
             * Function to check the current coast/brake mode status.
             * 
             * @return Current coast/brake mode status (check against MOTOR_COAST or MOTOR_BRAKE)
             */
            virtual uint32_t getCoastBrakeMode(void);

            /**
             * Function to set motor power.
             * 
             * @param uint32_t power
             * @return nothing
             */
            virtual void setPower(int32_t power) = 0;



    };

}

#endif
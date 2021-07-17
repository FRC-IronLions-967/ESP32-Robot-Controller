/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-20-2021

Last Updated: 6-20-2021

This header provides a virtual class (interface?) to allow for different types of encoders to be used.  In order to use whatever kind
of encoder you wish, simply create a class that pulls data from it and implements the following methods.  It can then be attached to
the MotorController and PWMServo classes for your use.

**************************************************************************************************************************************/

#ifndef TEAM967_ENCODER_H
#define TEAM967_ENCODER_H

#include <Arduino.h>

namespace team967 {
    
    /**
     * Virtual class that defines methods that should be implemented by all encoder objects.  This was implemented so that motor controllers can have a unified way to access encoder
     * data for more control options.
     */
    class Encoder {

        public:
            /**
             * Sets the count (number of ticks) on this encoder object.
             * 
             * @param count The number of ticks
             * @return nothing
             */
            virtual void setCount(int64_t count) = 0;

            /**
             * Returns the current count (number of ticks) that this encoder has counted.
             * 
             * @param none
             * @return The number of ticks as a 64 bit signed integer
             */
            virtual int64_t getCount(void) = 0;

            /**
             * Sets the number of clicks per rotation (CPR) of the encoder object.  This number is used to determine the values returned by the getRotations methods.
             * 
             * @param cpr The number of clicks per rotation (usually somewhere between 64 and 2048)
             * @return nothing
             */
            virtual void setCPR(uint16_t cpr) = 0;

            /**
             * Returns the number of clicks per rotation of the encoder object.
             * 
             * @param none
             * @return The number of clicks per rotation as a 16 bit unsigned integer
             */
            virtual uint16_t getCPR(void) = 0;

            /**
             * Returns the number of rotations rounded down to the closest integer value.  This can be useful if you do not want floating point value for whatever reason.
             * 
             * @param none
             * @return The number of rotations as a 64 bit signed integer
             */
            virtual int16_t getRotationsInt(void) = 0;

            /**
             * Returns the number of clicks above the last rotation.  In other words, if CPR = 128, and the encoder has counted 191 clicks, 63 will be returned.
             * 
             * @param none
             * @return The number of clicks above the last rotation as a 16 bit signed integer
             */
            virtual int16_t getRotationsRem(void) = 0;

            /**
             * Returns the number of rotations as a floating point.
             * 
             * @param none
             * @return The number of rotations as a floating point value
             */
            virtual double getRotationsDouble(void) = 0;

    };

}

#endif
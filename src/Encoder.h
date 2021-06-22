/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-20-2021

Last Updated: 6-20-2021

This header provides an abstract class (interface?) to allow for different types of encoders to be used.  In order to use whatever kind
of encoder you wish, simply create a class that pulls data from it and implements the following methods.  It can then be attached to
the MotorController and PWMServo classes for your use.

**************************************************************************************************************************************/

#ifndef TEAM967_ENCODER_H
#define TEAM967_ENCODER_H

#include <Arduino.h>

namespace team967 {
    
    class Encoder {

        public:
            // set the encoder count
            virtual void setCount(int64_t count) = 0;
            // get the count (in ticks) from the encoder
            virtual int64_t getCount(void) = 0;
            // set the number of clicks per rotation of the encoder
            virtual void setCPR(uint16_t cpr) = 0;
            // get the number of clicks per rotation of the encoder
            virtual uint16_t getCPR(void) = 0;
            // get the number of rotations as an integer
            virtual int64_t getRotationsInt(void) = 0;
            // get the number of clicks since the last rotation
            virtual int16_t getRotationsRem(void) = 0;
            // get the number of rotations as a floating point value
            virtual double getRotationsDouble(void) = 0;

    };

}

#endif
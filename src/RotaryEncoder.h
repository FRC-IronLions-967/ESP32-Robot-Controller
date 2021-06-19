/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-19-2021

Last Updated: 6-19-2021

This header provides a class that interfaces between madhephaestus's ESP32 encoder library and the format used by the other libraries
this repo provides for doing robot control.  Check out the library here: https://github.com/madhephaestus/ESP32Encoder/

This may be rewritten at some point in the future to have more features instead of relying on another library, but this will work for
now.

**************************************************************************************************************************************/

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <ESP32Encoder.h>

class RotaryEncoder {

    public:
        enum EncoderType {
            Single,
            Half,
            Full
        };


    private:
        uint8_t channelA;
        uint8_t channelB;
        uint16_t clicksPerRotation;
        EncoderType encoderType;
        ESP32Encoder encoder;


    public:
        // constructor and destructor, pinA and pinB are the pins the encoder is attached to, type is the type (single, half, full)
        // of encoder being used, and cpr is the number of clicks per rotation of the encoder, which defaults to 128
        RotaryEncoder(uint8_t pinA, uint8_t pinB, EncoderType type, uint16_t cpr = 128);
        ~RotaryEncoder(void);
        // attach rotary encoder to pins and begin counting
        void begin(void);
        // these functions are all just wrappers of the standard functions provided by the underlying class
        // sets count to a specified value
        void setCount(int64_t count);
        // gets the count from the interrupt handlers
        int64_t getCount(void);
        // clears count to 0
        int64_t clearCount(void);
        // pauses counting of new ticks
        int64_t pauseCount(void);
        // resumes counting of new ticks
        int64_t resumeCount(void);
        // this sets a filtering parameter for ignoring glitches in signals
        // read more about it here: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html
        void setFilter(uint16_t value);

        // these functions provide additional functionality
        uint16_t getCPR(void);
        void setCPR(uint16_t cpr);
        // returns the number of rotations as an integer, rounded down
        uint64_t getRotationsInt(void);
        // returns the number of clicks towards the next rotation (i.e. if cpr = 128, and count = 192, returns 64)
        uint16_t getRotationsRem(void);
        // returns the number of rotations as a decimal
        double getRotationsDouble(void);

};

#endif
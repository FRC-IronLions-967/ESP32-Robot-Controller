/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-19-2021

Last Updated: 6-20-2021

This header provides a class that interfaces between madhephaestus's ESP32 encoder library and the format used by the other libraries
this repo provides for doing robot control.  Check out the library here: https://github.com/madhephaestus/ESP32Encoder/

This may be rewritten at some point in the future to have more features instead of relying on another library, but this will work for
now.

**************************************************************************************************************************************/

#ifndef EXTERNALENCODER_H
#define EXTERNALENCODER_H

#include "Encoder.h"
#include <ESP32Encoder.h>

namespace team967 {

    /**
     * Class that provides a way to talk to externally connected encoders (ones that are not integrated into a motor controller or other peripheral).
     */
    class ExternalEncoder : public team967::Encoder {

        public:
            /**
             * Enum describing the different ways to measure the encoder pulses.  Single only uses one of the two channels, half uses both channels but measures only one edge of the
             * waveform, and full uses both channels and measures both the leading and trailing edges of the waveform.
             */
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
            /**
             * Constructor to create a new ExternalEncoder object with the specified options.
             * 
             * @param pinA The pin number for channel A of the encoder
             * @param pinB The pin number for channel B of the encoder, this will not be used in EncoderType::Single mode
             * @param type The type of measurement to use, @see EncoderType
             * @param cpr The number of clicks the encoder will send per each rotation, default is 128
             * @return A new ExternalEncoder object
             */
            ExternalEncoder(uint8_t pinA, uint8_t pinB, EncoderType type, uint16_t cpr = 128);

            /**
             * Destructor, stops the encoder counter, but does not change the pin assignments.  This can be done manually by the user if so desired.
             * 
             * @param none
             * @return nothing
             */
            ~ExternalEncoder(void);

            /**
             * Attaches the pins to the pulse counter and begins counting pulses.
             * 
             * @param none
             * @return nothing
             */
            void begin(void);

            /**
             * Sets the encoder count (clicks) to a specified value.
             * 
             * @param count A 64 bit signed integer specifying the number of clicks
             * @return nothing
             */
            void setCount(int64_t count);

            /**
             * Returns the number of clicks counted by the pulse counter.
             * 
             * @param none
             * @return The number of clicks as a 64 bit signed integer
             */
            int64_t getCount(void);

            /**
             * Zeros the click count in the pulse counter.
             * 
             * @param none
             * @return nothing
             */
            int64_t clearCount(void);

            /**
             * Stops the pulse counter from counting future ticks.  The pulse counter can be reenabled with resumeCount().
             * 
             * @param none
             * @return nothing
             */
            int64_t pauseCount(void);

            /**
             * Resumes the counting of ticks.  This should only be used after a call to pauseCount().
             * 
             * @param none
             * @return nothing
             */
            int64_t resumeCount(void);

            /**
             * Sets a filtering parameter for ignoring variances in signals.  Read more about this at:
             * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html
             * 
             * @param value The filter value to be used
             * @return nothing
             */
            void setFilter(uint16_t value);

            /**
             * Sets the clicks per rotation (CPR) value to be used by this encoder.
             * 
             * @param cpr The number of clicks per rotation
             * @return nothing
             */
            void setCPR(uint16_t cpr);

            /**
             * Returns the number of clicks per rotation for this object.
             * 
             * @param none
             * @return The number of clicks per rotation as a 16 bit unsigned integer
             */
            uint16_t getCPR(void);

            /**
             * Returns the number of rotations rounded down to the closest integer value.  This can be useful if you do not want floating point value for whatever reason.
             * 
             * @param none
             * @return The number of rotations as a 64 bit signed integer
             */
            int64_t getRotationsInt(void);

            /**
             * Returns the number of clicks above the last rotation.  In other words, if CPR = 128, and the encoder has counted 191 clicks, 63 will be returned.
             * 
             * @param none
             * @return The number of clicks above the last rotation as a 16 bit signed integer
             */
            int16_t getRotationsRem(void);

            /**
             * Returns the number of rotations as a floating point.
             * 
             * @param none
             * @return The number of rotations as a floating point value
             */
            double getRotationsDouble(void);

    };

}

#endif
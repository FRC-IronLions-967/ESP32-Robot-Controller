/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-19-2021

Last Updated: 6-20-2021

This header provides a class that uses the ESP32's pulse counting peripherals to interact with a quadrature encoder.  It was based off
of madhephaestus's ESP32 encoder library, which can be found here: https://github.com/madhephaestus/ESP32Encoder/

Unlike madhephaestus's library, this one also provides support for velocity measurements, which could prove useful, and provides the 
ability to set the number of clicks per rotation to get the number of rotations that have passed.

**************************************************************************************************************************************/

#ifndef EXTERNALENCODER_H
#define EXTERNALENCODER_H

#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/pcnt.h>
#include "Encoder.h"

namespace team967 {

    /**
     * Class that provides a way to talk to externally connected encoders (ones that are not integrated into a motor controller or other peripheral).
     */
    class ExternalEncoder : public Encoder {

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
            // port for A input channel
            gpio_num_t channelA;
            // port for B input channel
            gpio_num_t channelB;
            // number of clicks per rotation
            uint16_t clicksPerRotation;
            // type of encoder to use
            EncoderType encoderType;
            // whether or not this object is attached to an pulse counter
            bool attached;
            // whether or not this object should use pullup resistors
            bool pullUps;
            // id of the pulse counter this object is attached to
            pcnt_unit_t counterId;
            // current count
            int64_t count;
            // private member function to attach to a port
            bool attach();

            // static definitions for things that cannot be class members
            static const uint8_t MAX_ENCODERS;
            // interrupt handle for pulse counter
            static pcnt_isr_handle_t isrHandle;
            // static array of pulse counters
            static ExternalEncoder *encoders[];
            // whether or not the interrupt has been attached
            static bool attachedInterrupt;
            // interrupt handler
            static void IRAM_ATTR isrHandler(void *arg);


        public:
            /**
             * Encoder configuration field.  DO NOT USE.  It is public so that it can be accessed from the interrupt handler, which
             * must be static.
             */
            pcnt_config_t encConfig;

            /**
             * Time of last update.  DO NOT USE.  It is public so that it can be accessed from the interrupt handler.
             */
            uint64_t lastUpdate;

            /**
             * Value at time of last update.  DO NOT USE.  It is public so that it can be accessed from the interrupt handler.
             */
            int64_t lastValue;

            /**
             * Constructor to create a new ExternalEncoder object with the specified options.
             * 
             * @param pinA The pin number for channel A of the encoder
             * @param pinB The pin number for channel B of the encoder, this will not be used in EncoderType::Single mode
             * @param type The type of measurement to use, @see EncoderType
             * @param cpr The number of clicks the encoder will send per each rotation, default is 128
             * @return A new ExternalEncoder object
             */
            ExternalEncoder(uint8_t pinA, uint8_t pinB, EncoderType type, uint16_t cpr = 128, bool usePullUps = true);

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
             * @return The number of clicks as a 16 bit signed integer
             */
            int64_t getCount(void);

            /**
             * Zeros the click count in the pulse counter.
             * 
             * @param none
             * @return nothing
             */
            void clearCount(void);

            /**
             * Stops the pulse counter from counting future ticks.  The pulse counter can be reenabled with resumeCount().
             * 
             * @param none
             * @return nothing
             */
            void pauseCount(void);

            /**
             * Resumes the counting of ticks.  This should only be used after a call to pauseCount().
             * 
             * @param none
             * @return nothing
             */
            void resumeCount(void);

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
             * Returns the current velocity, in revolutions per second, of the encoder.
             * 
             * @param none
             * @return The speed in rotations per second
             */
            double getVelocity(void);

            /**
             * Returns the number of rotations rounded down to the closest integer value.  This can be useful if you do not want floating point value for whatever reason.
             * 
             * @param none
             * @return The number of rotations as a 64 bit signed integer
             */
            int16_t getRotationsInt(void);

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
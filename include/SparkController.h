#ifndef SPARKCONTROLLER_H
#define SPARKCONTROLLER_H

#include <Arduino.h>
#include <stdint.h>

namespace team967 {

    class SparkController {

        public:
            enum State {
                COAST,
                REVERSE,
                FORWARD,
                BRAKE
            };

        private:
            int fPin;
            int rPin;

            State state;

        public:
            SparkController(int forwardPin, int reversePin);

            ~SparkController();

            void begin();

            void forward();

            void reverse();

            void coast();

            void brake();

            State getState();

    };

}

#endif
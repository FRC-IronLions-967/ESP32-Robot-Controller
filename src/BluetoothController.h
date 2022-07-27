#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <stdint.h>

namespace team967 {

    class BluetoothController {

        public:
            virtual bool begin(void) = 0;

            virtual bool isConnected(void) = 0;

            virtual uint8_t getNumAxes(void) = 0;

            virtual int8_t getJoystickAxis(uint8_t id) = 0;

            virtual uint8_t getNumButtons(void) = 0;

            virtual bool isButtonPressed(uint8_t id) = 0;

    };

}

#endif
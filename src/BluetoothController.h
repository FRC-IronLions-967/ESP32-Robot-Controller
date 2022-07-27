#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <stdint.h>

namespace team967 {

    class BluetoothController {

        public:
            /**
             * Pure virtual function to be overridden in derived class.  Should start Bluetooth and return whether it was successful.
             * 
             * @return true if initialization was successful, false otherwise
             */
            virtual bool begin(void) = 0;

            /**
             * Pure virtual function to be overridden in derived class.  Returns whether the ESP32 is connected to the controller.
             * 
             * @return true if connected, false otherwise
             */
            virtual bool isConnected(void) = 0;

            /**
             * Pure virtual function to be overridden in derived class.  Returns the number of joystick axes the controller object has.
             * 
             * @return The number of axes
             */
            virtual uint8_t getNumAxes(void) = 0;

            /**
             * Pure virtual function to be overridden in derived class.  Returns the value of a joystick axis by id.
             * 
             * @param id The id of the axis to retrieve
             * @return the value of the joystick axis as a signed 8 bit integer (-128 to 127)
             */
            virtual int8_t getJoystickAxis(uint8_t id) = 0;

            /**
             * Pure virtual function to be overridden in derived class.  Returns the number of buttons the controller object has.
             * 
             * @return The number of buttons
             */
            virtual uint8_t getNumButtons(void) = 0;

            /**
             * Pure virtual function to be overridden in derived class.  Returns whether the button with the specified id is pressed
             * 
             * @param id The id of the button to retrieve
             * @return true if the button is pressed, false otherwise
             */
            virtual bool isButtonPressed(uint8_t id) = 0;

    };

}

#endif
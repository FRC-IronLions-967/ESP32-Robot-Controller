/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-6-2021

Last Updated: 6-21-2021

This header provides a class that allows for a more object-oriented approach to using the PS3 library for the ESP32 developed by
jvpernis, available here: https://github.com/jvpernis/esp32-ps3.  It allows for access to all of the buttons, analog sticks, and the
battery level of the controller.

In the future this class may be replaced with a more generic one, with subclasses for different controller types if more controller
support is added.

**************************************************************************************************************************************/

#ifndef BLUETOOTHGAMECONTROLLER_H
#define BLUETOOTHGAMECONTROLLER_H

#include "BluetoothController.h"
#include <Ps3Controller.h>
#include <stdint.h>

namespace team967 {

    /**
     * Class that provides access to a PS3 controller's button and joystick information.  Since the controller connects over Bluetooth, it only makes sense to instantiate one object
     * of this class at a time.
     */
    class BluetoothGameController : public BluetoothController {
    
        public:
            // constant definitions
            static const uint8_t NUM_BUTTONS = 17;

            static const uint8_t CROSS = 0;
            static const uint8_t SQUARE = 1;
            static const uint8_t TRIANGLE = 2;
            static const uint8_t CIRCLE = 3;
            static const uint8_t D_UP = 4;
            static const uint8_t D_DOWN = 5;
            static const uint8_t D_LEFT = 6;
            static const uint8_t D_RIGHT = 7;
            static const uint8_t LEFT_BUMP = 8;
            static const uint8_t RIGHT_BUMP = 9;
            static const uint8_t LEFT_TRIGGER = 10;
            static const uint8_t RIGHT_TRIGGER = 11;
            static const uint8_t LEFT_STICK = 12;
            static const uint8_t RIGHT_STICK = 13;
            static const uint8_t START = 14;
            static const uint8_t SELECT = 15;
            static const uint8_t PLAY_STATION = 16;

            static const uint8_t NUM_AXES = 4;

            static const uint8_t LEFT_STICK_X = 0;
            static const uint8_t LEFT_STICK_Y = 1;
            static const uint8_t RIGHT_STICK_X = 2;
            static const uint8_t RIGHT_STICK_Y = 3;

        private:
            // MAC address to connect to, must be modified inside the controller with SixAxisPairer
            char *m;
    
            // values for left and right sticks
            static int8_t rx;
            static int8_t ry;
            static int8_t lx;
            static int8_t ly;
    
            // array to store button states, true is pressed, false is not
            static bool buttons[17];
    
            // battery level
            static int battery;
    
            static void controller_update_callback();
    
    
        public:
            /**
             * Constructor to create a new BluetoothGameController object with the specified option.
             * 
             * @param mac The MAC address of the controller to connect to
             * @return A new BluetoothGameController object
             */
            BluetoothGameController(char *mac);

            /**
             * Destructor.  Disconnects from the control so Bluetooth can be used by something else.
             * 
             * @param none
             * @return nothing
             */
            ~BluetoothGameController(void);

            /**
             * Begins the connection with the controller.  After this is called, button and joystick values will begin to be updated.
             * 
             * @param none
             * @return true
             */
            bool begin(void);

            /**
             * Returns whether or not there is currently a valid connection between the ESP32 and the controller.  Can be useful to disable motors or other functionality in the event
             * that connection is lost.
             * 
             * @param none
             * @return true if connected, false otherwise
             */
            bool isConnected(void);

            /**
             * Returns the number of joystick axes on the PS3 Controller, which is always 4.  The joystick constants defined in this class can be used with this method.
             * 
             * @param none
             * @return The number of axes
             */
            uint8_t getNumAxes(void);

            /**
             * Returns the value of a joystick axis by id.
             * 
             * @param id the id of the axis to retrieve
             * @return The value of the specified axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getJoystickAxis(uint8_t id);

            /**
             * Returns the current value of the right stick's x-axis as an integer.
             * 
             * @param none
             * @return The value of the right stick's x-axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getRightStickX(void);

            /**
             * Returns the current value of the right stick's y-axis as an integer.
             * 
             * @param none
             * @return The value of the right stick's y-axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getRightStickY(void);

            /**
             * Returns the current value of the left stick's x-axis as an integer.
             * 
             * @param none
             * @return The value of the left stick's x-axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getLeftStickX(void);

            /**
             * Returns the current value of the left stick's y-axis as an integer.
             * 
             * @param none
             * @return The value of the left stick's y-axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getLeftStickY(void);

            /**
             * Returns the number of buttons on the PS3 Controller, which is always 17.
             * 
             * @param none
             * @return The number of buttons
             */
            uint8_t getNumButtons(void);

            /**
             * Returns the state of the specified button.  The button constants defined in this class can be used with this method.
             * 
             * @param id The numeric id of the button
             * @return true if the button is pressed, false otherwise
             */
            bool isButtonPressed(uint8_t id);

            /**
             * Returns the state of the battery of the controller.  States range from 0x05 (full) to 0x01 (controller shutdown). 0xEE is returned if the battery is charging.
             * 
             * @param none
             * @return The state of the battery
             */ 
            int getBattery(void);
    
    
    };

}

#endif

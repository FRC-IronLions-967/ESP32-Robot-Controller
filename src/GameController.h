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

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <Ps3Controller.h>
#include <stdint.h>

// definitions for the various buttons
#define CROSS 0
#define SQUARE 1
#define TRIANGLE 2
#define CIRCLE 3
#define D_UP 4
#define D_DOWN 5
#define D_LEFT 6
#define D_RIGHT 7
#define LEFT_BUMP 8
#define RIGHT_BUMP 9
#define LEFT_TRIGGER 10
#define RIGHT_TRIGGER 11
#define LEFT_STICK 12
#define RIGHT_STICK 13
#define START 14
#define SELECT 15
#define PS 16

namespace team967 {

    /**
     * Class that provides access to a PS3 controller's button and joystick information.  Since the controller connects over Bluetooth, it only makes sense to instantiate one object
     * of this class at a time.
     */
    class GameController {
    
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
             * Constructor to create a new GameController object with the specified option.
             * 
             * @param mac The MAC address of the controller to connect to
             * @return A new GameController object
             */
            GameController(char *mac);

            /**
             * Destructor for the GameController object.  Disconnects from the control so Bluetooth can be used by something else.
             * 
             * @param none
             * @return nothing
             */
            ~GameController(void);

            /**
             * Begins the connection with the controller.  After this is called, button and joystick values will begin to be updated.
             * 
             * @param none
             * @return nothing
             */
            void begin(void);

            /**
             * Returns whether or not there is currently a valid connection between the ESP32 and the controller.  Can be useful to disable motors or other functionality in the event
             * that connection is lost.
             * 
             * @param none
             * @return true if connected, false otherwise
             */
            bool isConnected(void);

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
             * Returns the state of the specified button.  Values can be passed in manually, but the defines at the top of this header can also be used for convenience.
             * 
             * @param button The numeric ID of the button
             * @return true if the button is pressed, false otherwise
             */
            bool isButtonPressed(uint8_t button);

            /**
             * Returns the state of the battery of the controller.  States range from 0x05 (full) to 0x01 (controller shutdown). 0xEE is returned if the battery is charging.
             * 
             * @param none
             * @return The state of the battery
             */ 
            int getBattery();
    
    
    };

}

#endif

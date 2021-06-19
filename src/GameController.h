/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-6-2021

Last Updated: 6-17-2021

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
#define UP 4
#define DOWN 5
#define LEFT 6
#define RIGHT 7
#define LEFT_BUMP 8
#define RIGHT_BUMP 9
#define LEFT_TRIGGER 10
#define RIGHT_TRIGGER 11
#define LEFT_STICK 12
#define RIGHT_STICK 13
#define START 14
#define SELECT 15
#define PS 16

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
        GameController(char *mac);
        ~GameController(void);
        void begin(void);
        bool isConnected(void);
        int8_t getRightStickX(void);
        int8_t getRightStickY(void);
        int8_t getLeftStickX(void);
        int8_t getLeftStickY(void);
        bool isButtonPressed(uint8_t button);     
        int getBattery();


};

#endif
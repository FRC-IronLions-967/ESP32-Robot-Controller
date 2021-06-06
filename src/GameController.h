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
        void begin();
        bool isConnected();
        int8_t getRightStickX();
        int8_t getRightStickY();
        int8_t getLeftStickX();
        int8_t getLeftStickY();
        bool isButtonPressed(uint8_t button);     
        int getBattery();


};

#endif
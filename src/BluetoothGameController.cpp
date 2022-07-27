/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-6-2021

Last Updated: 6-21-2021

This file provides the definitions of the methods declared in BluetoothGameController.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include "BluetoothGameController.h"

int8_t team967::BluetoothGameController::rx = 0;
int8_t team967::BluetoothGameController::ry = 0;
int8_t team967::BluetoothGameController::lx = 0;
int8_t team967::BluetoothGameController::ly = 0;

bool team967::BluetoothGameController::buttons[17];

int team967::BluetoothGameController::battery = 0;

void team967::BluetoothGameController::controller_update_callback() {
    buttons[CROSS] = Ps3.data.button.cross;
    buttons[SQUARE] = Ps3.data.button.square;
    buttons[TRIANGLE] = Ps3.data.button.triangle;
    buttons[CIRCLE] = Ps3.data.button.circle;
    buttons[D_UP] = Ps3.data.button.up;
    buttons[D_DOWN] = Ps3.data.button.down;
    buttons[D_LEFT] = Ps3.data.button.left;
    buttons[D_RIGHT] = Ps3.data.button.right;
    buttons[LEFT_BUMP] = Ps3.data.button.l1;
    buttons[RIGHT_BUMP] = Ps3.data.button.r1;
    buttons[LEFT_TRIGGER] = Ps3.data.button.l2;
    buttons[RIGHT_TRIGGER] = Ps3.data.button.r2;
    buttons[LEFT_STICK] = Ps3.data.button.l3;
    buttons[RIGHT_STICK] = Ps3.data.button.r3;
    buttons[START] = Ps3.data.button.start;
    buttons[SELECT] = Ps3.data.button.select;
    buttons[PS] = Ps3.data.button.ps;

    rx = Ps3.data.analog.stick.rx;
    ry = Ps3.data.analog.stick.ry;
    lx = Ps3.data.analog.stick.lx;
    ly = Ps3.data.analog.stick.ly;

    battery = Ps3.data.status.battery;
}

team967::BluetoothGameController::BluetoothGameController(char *mac): m(mac) {
    Ps3.attach(controller_update_callback);
}

team967::BluetoothGameController::~BluetoothGameController() {
    Ps3.end();
}

bool team967::BluetoothGameController::begin() {
    Ps3.begin(m);

    return true;
}

bool team967::BluetoothGameController::isConnected() {
    return Ps3.isConnected();
}

uint8_t team967::BluetoothGameController::getNumAxes() {
    return NUM_AXES;
}

int8_t team967::BluetoothGameController::getJoystickAxis(uint8_t id) {
    switch(id) {
        case LEFT_STICK_X:
            return lx;

        case LEFT_STICK_Y:
            return ly;

        case RIGHT_STICK_X:
            return rx;

        case RIGHT_STICK_Y:
            return ry;

        default:
            return 0;
    }
}

int8_t team967::BluetoothGameController::getRightStickX() {
    return rx;
}

int8_t team967::BluetoothGameController::getRightStickY() {
    return ry;
}

int8_t team967::BluetoothGameController::getLeftStickX() {
    return lx;
}

int8_t team967::BluetoothGameController::getLeftStickY() {
    return ly;
}

uint8_t team967::BluetoothGameController::getNumButtons() {
    return NUM_BUTTONS;
}

bool team967::BluetoothGameController::isButtonPressed(uint8_t id) {
    if(id >= NUM_BUTTONS) return false;

    return buttons[id];
}

int team967::BluetoothGameController::getBattery() {
    return battery;
}

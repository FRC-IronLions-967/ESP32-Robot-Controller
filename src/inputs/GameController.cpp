/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-6-2021

Last Updated: 6-17-2021

This file provides the definitions of the methods declared in GameController.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include "GameController.h"

int8_t team967::GameController::rx = 0;
int8_t team967::GameController::ry = 0;
int8_t team967::GameController::lx = 0;
int8_t team967::GameController::ly = 0;

bool team967::GameController::buttons[17];

int team967::GameController::battery = 0;

void team967::GameController::controller_update_callback() {
    buttons[CROSS] = Ps3.data.button.cross;
    buttons[SQUARE] = Ps3.data.button.square;
    buttons[TRIANGLE] = Ps3.data.button.triangle;
    buttons[CIRCLE] = Ps3.data.button.circle;
    buttons[UP] = Ps3.data.button.up;
    buttons[DOWN] = Ps3.data.button.down;
    buttons[LEFT] = Ps3.data.button.left;
    buttons[RIGHT] = Ps3.data.button.right;
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

team967::GameController::GameController(char *mac): m(mac) {
    Ps3.attach(controller_update_callback);
}

team967::GameController::~GameController() {
    Ps3.end();
}

void team967::GameController::begin() {
    Ps3.begin(m);
}

bool team967::GameController::isConnected() {
    return Ps3.isConnected();
}

int8_t team967::GameController::getRightStickX() {
    return rx;
}

int8_t team967::GameController::getRightStickY() {
    return ry;
}

int8_t team967::GameController::getLeftStickX() {
    return lx;
}

int8_t team967::GameController::getLeftStickY() {
    return ly;
}

bool team967::GameController::isButtonPressed(uint8_t button) {
    if(button > 16) return false;

    return buttons[button];
}

int team967::GameController::getBattery() {
    return battery;
}
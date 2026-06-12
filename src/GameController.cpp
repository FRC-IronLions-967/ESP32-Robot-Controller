// /**************************************************************************************************************************************

// Author(s): Nathan Stark

// Created: 6-6-2021

// Last Updated: 6-4-2026

// This file provides the definitions of the methods declared in GameController.h.  Please see that file for more details.

// **************************************************************************************************************************************/

#include <GameController.h>

GamepadPtr team967::GameController::controllers[BP32_MAX_GAMEPADS] = {};

bool team967::GameController::isConnected[BP32_MAX_GAMEPADS] = {};

bool team967::GameController::isObject[BP32_MAX_GAMEPADS] = {};

void team967::GameController::onConnectedController(ControllerPtr ctl) {
    Serial.println("Inside onConnectedController");
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (!isConnected[i]) {
            controllers[i] = ctl;
            isConnected[i] = true;

            break;
        }
    }
}

void team967::GameController::onDisconnectedController(ControllerPtr ctl) {
    Serial.println("Inside onDisconnectedController");
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (isConnected[i] && controllers[i] == ctl) {
            controllers[i] = nullptr;
            isConnected[i] = false;

            break;
        }
    }
}

team967::GameController::GameController(int gamepadIndex) : gamepadIndex(gamepadIndex) {
    isObject[gamepadIndex] = true;
}

team967::GameController* team967::GameController::waitForConnection(void) {
    bool foundController = false;
    while(!foundController) {
        for(int i = 0; i < BP32_MAX_GAMEPADS; i++) {
            if(isConnected[i] && !isObject[i]) {
                return new GameController(i);
            }
        }

        update();
    }
}

team967::GameController::~GameController(void) {
    isObject[gamepadIndex] = false;
}

void team967::GameController::begin(void) {
    for(int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        controllers[i] = nullptr;
        isConnected[i] = false;
        isObject[i] = false;
    }

    BP32.enableVirtualDevice(false);

    // This call is mandatory. It sets up Bluepad32 and creates the callbacks.
    ControllerCallback onConnectedCallback = team967::GameController::onConnectedController;
    ControllerCallback onDisconnectedCallback = team967::GameController::onDisconnectedController;

    BP32.setup(onConnectedCallback, onDisconnectedCallback);

    BP32.forgetBluetoothKeys();
}

void team967::GameController::update(void) {
    BP32.update();
}

GamepadPtr &team967::GameController::get(void) {
    return controllers[gamepadIndex];
}
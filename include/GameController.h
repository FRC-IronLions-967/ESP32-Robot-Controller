// /**************************************************************************************************************************************

// Author(s): Nathan Stark

// Created: 6-6-2021

// Last Updated: 6-4-2026

// This header provides a class that allows for an object oriented way to interface with generic Bluepad32 controllers.

// **************************************************************************************************************************************/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <Bluepad32.h>

#include <stdint.h>

namespace team967 {

    /**
     * Class that provides access to a Bluepad32 controllers with a little bit of wrapping.
     */
    class GameController {
    
        private:
            int gamepadIndex;

            static GamepadPtr controllers[BP32_MAX_GAMEPADS];

            static bool isConnected[BP32_MAX_GAMEPADS];

            static bool isObject[BP32_MAX_GAMEPADS];

            static void onConnectedController(ControllerPtr ctl);

            static void onDisconnectedController(ControllerPtr ctl);

            /**
             * Private constructor to make sure users can't create more controllers than we support.
             */
            GameController(int gamepadIndex);
    
    
        public:
            /**
             * Wait until a controller connects, then return a new instance of this class.
             * 
             * @param none
             * @return pointer to a GameController object
             */
            static GameController* waitForConnection(void);

            /**
             * If a new controller connection is available, connect to it, otherwise return false.
             * 
             * @param gameController Pointer to GameController pointer that will have result placed in it
             * @return true if a controller was connected, false otherwise
             */
            static bool attemptConnection(GameController** gameController);

            /**
             * Destructor for the GameController object.  Disconnects from the control so Bluetooth can be used by something else.
             * 
             * @param none
             * @return nothing
             */
            ~GameController(void);

            /**
             * Function to initialize Bluepad32, by default pairing will be disabled until manually enabled to prevent issues.
             * 
             * @param none
             * @return nothing
             */
            static void begin(void);

            /**
             * Function to enable pairing, pairing mode will last until a controller is connected or manually disabled.
             * 
             * @param none
             * @return nothing
             */
            static void enablePairing(void);

            /**
             * Function to manually disable pairing mode.
             */
            static void disablePairing(void);

            /**
             * Updates the gamepad with the latest values, should be called inside a loop.
             * 
             * @param none
             * @return nothing
             */
            static void update(void);

            /**
             * Returns a reference to the GamepadPtr object that is connected.
             * 
             * @param none
             * @return nothing
             */
            GamepadPtr& get();    
    
    };

}

#endif

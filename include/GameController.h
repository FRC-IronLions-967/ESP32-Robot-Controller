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
             * Destructor for the GameController object.  Disconnects from the control so Bluetooth can be used by something else.
             * 
             * @param none
             * @return nothing
             */
            ~GameController(void);

            /**
             * Function to begin listening for incoming controller connections to be able to create new instances of this
             * class.  Should be called before anything else in this class.
             * 
             * @param none
             * @return nothing
             */
            static void begin(void);

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

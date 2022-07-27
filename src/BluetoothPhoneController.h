#ifndef BLUETOOTHPHONECONTROLLER_H
#define BLUETOOTHPHONECONTROLLER_H

#include "BluetoothController.h"
#include "BluetoothSerial.h"
#include <stdint.h>

namespace team967 {

    struct BtPacket {
      uint8_t type;
      uint8_t rev;
      uint8_t numJoysticks;
      uint8_t numButtons;
      int8_t* joystickVals;
      bool* buttonVals;
    };

    class BluetoothPhoneController : public BluetoothController {

        private:
            // only one instance of this class can exist
            static BluetoothPhoneController* inst;

            static bool hasData;
        
            // object to communicate with Bluetooth similar to how the Serial interface works
            BluetoothSerial bt;

            // name of this device
            char* btName;

            // whether or not a valid device is connected
            bool connected;

            BtPacket* state;

            // callback function that will be called when a device connects, disconnects, or new data becomes available
            static void btCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t* param);

            // constructor
            // this device's bluetooth name will be set to name
            BluetoothPhoneController(char* name);

            void updateState(BtPacket* data);

            void setConnected(bool c);

        public:
            static BluetoothPhoneController& createInstance(char* name);
        
            // destructor
            ~BluetoothPhoneController();

            // starts Bluetooth and starts listening for connections
            bool begin(void);

            // checks whether or not this object has a valid connection
            bool isConnected(void);

            uint8_t getNumAxes(void);

            int8_t getJoystickAxis(uint8_t id);

            // returns the number of joysticks this controller has
            uint8_t getNumJoysticks(void);

            // returns the x axis value of the joystick with the given id
            int8_t getJoystickX(uint8_t id);

            // returns the y axis value of the joystick with the given id
            int8_t getJoystickY(uint8_t id);

            // returns the number of buttons this controller has
            uint8_t getNumButtons();

            // returns whether the button with the given id is pressed
            bool isButtonPressed(uint8_t id);

    };

}

#endif

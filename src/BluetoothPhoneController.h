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
            /**
             * Creates a new instance of this class and sets it as the global instance.  Only one instance of this class can exist at a time.
             * 
             * @param name Bluetooth device name to use for this device
             * @return Reference to the global instance
             */
            static BluetoothPhoneController& createInstance(char* name);
        
            /**
             * Destructor.
             */
            ~BluetoothPhoneController();

            /**
             * Starts Bluetooth and allows incoming devices to connect.  Waiting for devices to connect is non-blocking.
             * 
             * @return true if Bluetooth initializes successfully, false otherwise
             */
            bool begin(void);

            /**
             * Returns whether the ESP32 is connected to a phone acting as a joystick.
             * 
             * @return true if connected, false otherwise
             */
            bool isConnected(void);

            /**
             * Returns the number of joystick axes on the phone controller, which can vary.  (Robotics app has 4)
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
             * Returns the number of joysticks on the phone controller.
             * 
             * @param none
             * @return The number of joysticks
             */
            uint8_t getNumJoysticks(void);

            /**
             * Returns the x axis value of the joystick with the specified id.
             * 
             * @param id the id of the joystick to retrieve
             * @return The value of the x axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getJoystickX(uint8_t id);

            /**
             * Returns the y axis value of the joystick with the specified id.
             * 
             * @param id the id of the joystick to retrieve
             * @return The value of the y axis as a 8 bit signed integer (-128 to 127)
             */
            int8_t getJoystickY(uint8_t id);

            /**
             * Returns the number of buttons on the phone controller, which can vary.  (Robotics app has 4)
             * 
             * @param none
             * @return The number of buttons
             */
            uint8_t getNumButtons();

            /**
             * Returns the state of the specified button.
             * 
             * @param id The numeric id of the button
             * @return true if the button is pressed, false otherwise
             */
            bool isButtonPressed(uint8_t id);

    };

}

#endif

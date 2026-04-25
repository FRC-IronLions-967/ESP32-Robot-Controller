#include <Arduino.h>
#include <Bluepad32.h>

#include <DRV8873MotorController.h>

team967::DRV8873MotorController motorController(47, 21, 10000, 9);

void setup() {
  Serial.begin(115200);

  while(!Serial);

  Serial.println("Begin prints");

  motorController.begin();

  // ledcAttachPin(21, 0);
}

void loop() {
  // Serial.println("Periodic");

  motorController.setPower(255);

  // ledcWrite(21, 255);

  delay(1000);
}

// GamepadPtr myControllers[BP32_MAX_GAMEPADS] = {};

// team967::DRV8873MotorController *motorController;

// void onConnectedController(ControllerPtr ctl);

// void onDisconnectedController(ControllerPtr ctl);

// void setup() {
//   Serial.begin(115200);

//   while(!Serial);

//   delay(2000);

//   // while(1) {
//     Serial.println("Hello World");
//   // }

//   motorController = new team967::DRV8873MotorController(47, 21, 0, 10000, 9);

//   String fv = BP32.firmwareVersion();
//   Serial.print("Firmware version installed: ");
//   Serial.println(fv);

//   // To get the BD Address (MAC address) call:
//   const uint8_t* addr = BP32.localBdAddress();
//   Serial.print("BD Address: ");
//   for (int i = 0; i < 6; i++) {
//     Serial.print(addr[i], HEX);
//     if (i < 5)
//       Serial.print(":");
//     else
//       Serial.println();
//   }

//   // This call is mandatory. It sets up Bluepad32 and creates the callbacks.
//   BP32.setup(&onConnectedController, &onDisconnectedController);

//   BP32.forgetBluetoothKeys();
// }

// // This callback gets called any time a new gamepad is connected.
// // Up to 4 gamepads can be connected at the same time.
// void onConnectedController(ControllerPtr ctl) {
//   bool foundEmptySlot = false;
//   for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
//     if (myControllers[i] == nullptr) {
//       Serial.print("CALLBACK: Controller is connected, index=");
//       Serial.println(i);
//       myControllers[i] = ctl;
//       foundEmptySlot = true;

//       // Optional, once the gamepad is connected, request further info about the
//       // gamepad.
//       ControllerProperties properties = ctl->getProperties();
//       char buf[80];
//       sprintf(buf,
//               "BTAddr: %02x:%02x:%02x:%02x:%02x:%02x, VID/PID: %04x:%04x, "
//               "flags: 0x%02x",
//               properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
//               properties.btaddr[3], properties.btaddr[4], properties.btaddr[5],
//               properties.vendor_id, properties.product_id, properties.flags);
//       Serial.println(buf);
//       break;
//     }
//   }
//   if (!foundEmptySlot) {
//     Serial.println(
//         "CALLBACK: Controller connected, but could not found empty slot");
//   }
// }

// void onDisconnectedController(ControllerPtr ctl) {
//   bool foundGamepad = false;

//   for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
//     if (myControllers[i] == ctl) {
//       Serial.print("CALLBACK: Controller is disconnected from index=");
//       Serial.println(i);
//       myControllers[i] = nullptr;
//       foundGamepad = true;
//       break;
//     }
//   }

//   if (!foundGamepad) {
//     Serial.println(
//         "CALLBACK: Controller disconnected, but not found in myControllers");
//   }
// }

// void processGamepad(ControllerPtr gamepad) {
//   // There are different ways to query whether a button is pressed.
//   // By query each button individually:
//   //  a(), b(), x(), y(), l1(), etc...

//   if (gamepad->a()) {
//     static int colorIdx = 0;
//     // Some gamepads like DS4 and DualSense support changing the color LED.
//     // It is possible to change it by calling:
//     switch (colorIdx % 3) {
//       case 0:
//         // Red
//         gamepad->setColorLED(255, 0, 0);
//         break;
//       case 1:
//         // Green
//         gamepad->setColorLED(0, 255, 0);
//         break;
//       case 2:
//         // Blue
//         gamepad->setColorLED(0, 0, 255);
//         break;
//     }
//     colorIdx++;
//   }

//   if (gamepad->b()) {
//     // Turn on the 4 LED. Each bit represents one LED.
//     static int led = 0;
//     led++;
//     // Some gamepads like the DS3, DualSense, Nintendo Wii, Nintendo Switch
//     // support changing the "Player LEDs": those 4 LEDs that usually indicate
//     // the "gamepad seat".
//     // It is possible to change them by calling:
//     gamepad->setPlayerLEDs(led & 0x0f);
//   }

//   if (gamepad->x()) {
//     // Duration: 255 is ~2 seconds
//     // force: intensity
//     // Some gamepads like DS3, DS4, DualSense, Switch, Xbox One S support
//     // rumble.
//     // It is possible to set it by calling:
//     gamepad->setRumble(0xc0 /* force */, 0xc0 /* duration */);
//   }

//   // Another way to query the buttons, is by calling buttons(), or
//   // miscButtons() which return a bitmask.
//   // Some gamepads also have DPAD, axis and more.
//   char buf[256];
//   snprintf(buf, sizeof(buf) - 1,
//            "idx=%d, dpad: 0x%02x, buttons: 0x%04x, "
//            "axis L: %4li, %4li, axis R: %4li, %4li, "
//            "brake: %4ld, throttle: %4li, misc: 0x%02x, "
//            "gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d, "
//            "battery: %d",
//            gamepad->index(),        // Gamepad Index
//            gamepad->dpad(),         // DPad
//            gamepad->buttons(),      // bitmask of pressed buttons
//            gamepad->axisX(),        // (-511 - 512) left X Axis
//            gamepad->axisY(),        // (-511 - 512) left Y axis
//            gamepad->axisRX(),       // (-511 - 512) right X axis
//            gamepad->axisRY(),       // (-511 - 512) right Y axis
//            gamepad->brake(),        // (0 - 1023): brake button
//            gamepad->throttle(),     // (0 - 1023): throttle (AKA gas) button
//            gamepad->miscButtons(),  // bitmask of pressed "misc" buttons
//            gamepad->gyroX(),        // Gyro X
//            gamepad->gyroY(),        // Gyro Y
//            gamepad->gyroZ(),        // Gyro Z
//            gamepad->accelX(),       // Accelerometer X
//            gamepad->accelY(),       // Accelerometer Y
//            gamepad->accelZ(),       // Accelerometer Z
//            gamepad->battery()       // 0=Unknown, 1=empty, 255=full
//   );
//   Serial.println(buf);

//   // You can query the axis and other properties as well. See
//   // Controller.h For all the available functions.
// }

// void loop() {
//   // This call fetches all the controller info from the NINA (ESP32) module.
//   // Call this function in your main loop.
//   // The controllers' pointer (the ones received in the callbacks) gets updated
//   // automatically.
//   BP32.update();

//   // It is safe to always do this before using the controller API.
//   // This guarantees that the controller is valid and connected.
//   for (int i = 0; i < BP32_MAX_CONTROLLERS; i++) {
//     ControllerPtr myController = myControllers[i];

//     if (myController && myController->isConnected()) {
//       if (myController->isGamepad())
//         processGamepad(myController);
//     }
//   }

//   motorController->setPower(myControllers[0]->axisX());

//   delay(150);
// }

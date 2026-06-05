#include <Arduino.h>
#include <Bluepad32.h>

#include <ESP32S3Rev1BoardPinDefs.h>

#include <DRV8873MotorController.h>
#include <ESP32S3LegacyMCPWMChannel.h>
#include <ESP32S3SPIMaster.h>
#include <PWMServo.h>

using namespace team967;

GamepadPtr myControllers[BP32_MAX_GAMEPADS] = {};

ESP32S3LegacyMCPWMChannel mcpwmChannel0(0, 0, MOTOR_CONTROLLER_0_IN1_PIN, MOTOR_CONTROLLER_0_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel1(0, 1, MOTOR_CONTROLLER_1_IN1_PIN, MOTOR_CONTROLLER_1_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel2(0, 2, MOTOR_CONTROLLER_2_IN1_PIN, MOTOR_CONTROLLER_2_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel3(1, 0, MOTOR_CONTROLLER_3_IN1_PIN, MOTOR_CONTROLLER_3_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel4(1, 1, MOTOR_CONTROLLER_4_IN1_PIN, MOTOR_CONTROLLER_4_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel5(1, 2, MOTOR_CONTROLLER_5_IN1_PIN, MOTOR_CONTROLLER_5_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);

ESP32S3SPIMaster motorControllerSPI0(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_0_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI1(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_1_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI2(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_2_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI3(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_3_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI4(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_4_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI5(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_5_PIN, SPI_FREQUENCY);

DRV8873MotorController motorController0(&mcpwmChannel0, &motorControllerSPI0);
DRV8873MotorController motorController1(&mcpwmChannel1, &motorControllerSPI1);
DRV8873MotorController motorController2(&mcpwmChannel2, &motorControllerSPI2);
DRV8873MotorController motorController3(&mcpwmChannel3, &motorControllerSPI3);
DRV8873MotorController motorController4(&mcpwmChannel4, &motorControllerSPI4);
DRV8873MotorController motorController5(&mcpwmChannel5, &motorControllerSPI5);

PWMServo servo0(GPIO_SERVO_0_PIN, 0, DEFAULT_PWM_FREQ, 14);
PWMServo servo1(GPIO_SERVO_1_PIN, 1, DEFAULT_PWM_FREQ, 14);
PWMServo servo2(GPIO_SERVO_2_PIN, 2, DEFAULT_PWM_FREQ, 14);
PWMServo servo3(GPIO_SERVO_3_PIN, 3, DEFAULT_PWM_FREQ, 14);
PWMServo servo4(GPIO_SERVO_4_PIN, 4, DEFAULT_PWM_FREQ, 14);

void onConnectedController(ControllerPtr ctl);

void onDisconnectedController(ControllerPtr ctl);

void setup() {
  Serial.begin(115200);

  while(!Serial);

  delay(2000);

  Serial.println("Start serial prints in main core");

  // motorController.begin();
  motorController0.begin();
  motorController1.begin();
  motorController2.begin();
  motorController3.begin();
  motorController4.begin();
  motorController5.begin();

  servo0.begin();
  servo1.begin();
  servo2.begin();
  servo3.begin();
  servo4.begin();

  Serial.println("Past motor controller begin");

  uint8_t readData = 0;

  // motorController0.readRegister(0, &readData);

  // Serial.print("Motor controller 0 fault reg: ");
  // Serial.println(readData);

  // motorController0.readRegister(1, &readData);

  // Serial.print("Motor controller 0 diag reg: ");
  // Serial.println(readData);

  // motorController0.readRegister(2, &readData);

  // Serial.print("Motor controller 0 IC1 reg: ");
  // Serial.println(readData);

  // motorController0.writeRegister(2, 0xDD, &readData);

  // motorController0.readRegister(2, &readData);

  // motorController0.writeRegister(3, 0xEE, &readData);

  // motorController0.readRegister(3, &readData);

  // motorController0.writeRegister(5, 0x0C, &readData);

  // motorController0.readRegister(5, &readData);


  // motorController1.writeRegister(2, 0xDD, &readData);

  // motorController1.readRegister(2, &readData);

  // motorController1.writeRegister(3, 0xEE, &readData);

  // motorController1.readRegister(3, &readData);

  // motorController1.writeRegister(5, 0x0C, &readData);

  // motorController1.readRegister(5, &readData);


  // motorController2.writeRegister(2, 0xDD, &readData);

  // motorController2.readRegister(2, &readData);

  // motorController2.writeRegister(3, 0xEE, &readData);

  // motorController2.readRegister(3, &readData);

  // motorController2.writeRegister(5, 0x0C, &readData);

  // motorController2.readRegister(5, &readData);

  Serial.print("Motor controller 1 IC1 reg: ");
  Serial.println(readData);

  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);

  // To get the BD Address (MAC address) call:
  const uint8_t* addr = BP32.localBdAddress();
  Serial.print("BD Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(addr[i], HEX);
    if (i < 5)
      Serial.print(":");
    else
      Serial.println();
  }

  BP32.enableVirtualDevice(false);

  // This call is mandatory. It sets up Bluepad32 and creates the callbacks.
  BP32.setup(&onConnectedController, &onDisconnectedController);

  Serial.println("Past BP32.setup()");

  BP32.forgetBluetoothKeys();
}

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.print("CALLBACK: Controller is connected, index=");
      Serial.println(i);
      myControllers[i] = ctl;
      foundEmptySlot = true;

      // Optional, once the gamepad is connected, request further info about the
      // gamepad.
      ControllerProperties properties = ctl->getProperties();
      char buf[80];
      sprintf(buf,
              "BTAddr: %02x:%02x:%02x:%02x:%02x:%02x, VID/PID: %04x:%04x, "
              "flags: 0x%02x",
              properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
              properties.btaddr[3], properties.btaddr[4], properties.btaddr[5],
              properties.vendor_id, properties.product_id, properties.flags);
      Serial.println(buf);
      break;
    }
  }
  if (!foundEmptySlot) {
    Serial.println(
        "CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundGamepad = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.print("CALLBACK: Controller is disconnected from index=");
      Serial.println(i);
      myControllers[i] = nullptr;
      foundGamepad = true;
      break;
    }
  }

  if (!foundGamepad) {
    Serial.println(
        "CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

void processGamepad(ControllerPtr gamepad) {
  // There are different ways to query whether a button is pressed.
  // By query each button individually:
  //  a(), b(), x(), y(), l1(), etc...

  if (gamepad->a()) {
    static int colorIdx = 0;
    // Some gamepads like DS4 and DualSense support changing the color LED.
    // It is possible to change it by calling:
    switch (colorIdx % 3) {
      case 0:
        // Red
        gamepad->setColorLED(255, 0, 0);
        break;
      case 1:
        // Green
        gamepad->setColorLED(0, 255, 0);
        break;
      case 2:
        // Blue
        gamepad->setColorLED(0, 0, 255);
        break;
    }
    colorIdx++;
  }

  if (gamepad->b()) {
    // Turn on the 4 LED. Each bit represents one LED.
    static int led = 0;
    led++;
    // Some gamepads like the DS3, DualSense, Nintendo Wii, Nintendo Switch
    // support changing the "Player LEDs": those 4 LEDs that usually indicate
    // the "gamepad seat".
    // It is possible to change them by calling:
    gamepad->setPlayerLEDs(led & 0x0f);
  }

  if (gamepad->x()) {
    // Duration: 255 is ~2 seconds
    // force: intensity
    // Some gamepads like DS3, DS4, DualSense, Switch, Xbox One S support
    // rumble.
    // It is possible to set it by calling:
    gamepad->setRumble(0xc0 /* force */, 0xc0 /* duration */);
  }

  // Another way to query the buttons, is by calling buttons(), or
  // miscButtons() which return a bitmask.
  // Some gamepads also have DPAD, axis and more.
  char buf[256];
  snprintf(buf, sizeof(buf) - 1,
           "idx=%d, dpad: 0x%02x, buttons: 0x%04x, "
           "axis L: %4li, %4li, axis R: %4li, %4li, "
           "brake: %4ld, throttle: %4li, misc: 0x%02x, "
           "gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d, "
           "battery: %d",
           gamepad->index(),        // Gamepad Index
           gamepad->dpad(),         // DPad
           gamepad->buttons(),      // bitmask of pressed buttons
           gamepad->axisX(),        // (-511 - 512) left X Axis
           gamepad->axisY(),        // (-511 - 512) left Y axis
           gamepad->axisRX(),       // (-511 - 512) right X axis
           gamepad->axisRY(),       // (-511 - 512) right Y axis
           gamepad->brake(),        // (0 - 1023): brake button
           gamepad->throttle(),     // (0 - 1023): throttle (AKA gas) button
           gamepad->miscButtons(),  // bitmask of pressed "misc" buttons
           gamepad->gyroX(),        // Gyro X
           gamepad->gyroY(),        // Gyro Y
           gamepad->gyroZ(),        // Gyro Z
           gamepad->accelX(),       // Accelerometer X
           gamepad->accelY(),       // Accelerometer Y
           gamepad->accelZ(),       // Accelerometer Z
           gamepad->battery()       // 0=Unknown, 1=empty, 255=full
  );
  // Serial.println(buf);

  // You can query the axis and other properties as well. See
  // Controller.h For all the available functions.
}

void loop() {
  // This call fetches all the controller info from the NINA (ESP32) module.
  // Call this function in your main loop.
  // The controllers' pointer (the ones received in the callbacks) gets updated
  // automatically.
  BP32.update();

  // It is safe to always do this before using the controller API.
  // This guarantees that the controller is valid and connected.
  for (int i = 0; i < BP32_MAX_CONTROLLERS; i++) {
    ControllerPtr myController = myControllers[i];

    if (myController && myController->isConnected()) {
      if (myController->isGamepad())
        processGamepad(myController);
    }
  }

  if(myControllers[0] && myControllers[0]->isConnected()) {
    motorController0.setPower(myControllers[0]->axisX());
    motorController1.setPower(myControllers[0]->axisX());
    motorController2.setPower(myControllers[0]->axisX());
    motorController3.setPower(myControllers[0]->axisX());
    motorController4.setPower(myControllers[0]->axisX());
    motorController5.setPower(myControllers[0]->axisX());

    servo0.setAngleDegrees(myControllers[0]->axisRX() / 6);
    servo1.setAngleDegrees(myControllers[0]->axisRX() / 6);
    servo2.setAngleDegrees(myControllers[0]->axisRX() / 6);
    servo3.setAngleDegrees(myControllers[0]->axisRX() / 6);
    servo4.setAngleDegrees(myControllers[0]->axisRX() / 6);

    if(myControllers[0]->a()) {
      uint8_t readData = 0;

      motorController0.readRegister(0, &readData);

      Serial.print("Motor controller 0 status reg: ");
      Serial.println(readData);

      motorController0.readRegister(1, &readData);

      Serial.print("Motor controller 0 diag reg: ");
      Serial.println(readData);



      motorController1.readRegister(0, &readData);

      Serial.print("Motor controller 1 status reg: ");
      Serial.println(readData);

      motorController1.readRegister(1, &readData);

      Serial.print("Motor controller 1 diag reg: ");
      Serial.println(readData);

      motorController2.readRegister(0, &readData);

      Serial.print("Motor controller 2 status reg: ");
      Serial.println(readData);

      motorController2.readRegister(1, &readData);

      Serial.print("Motor controller 2 diag reg: ");
      Serial.println(readData);

      motorController3.readRegister(0, &readData);

      Serial.print("Motor controller 3 status reg: ");
      Serial.println(readData);

      motorController3.readRegister(1, &readData);

      Serial.print("Motor controller 3 diag reg: ");
      Serial.println(readData);

      motorController4.readRegister(0, &readData);

      Serial.print("Motor controller 4 status reg: ");
      Serial.println(readData);

      motorController4.readRegister(1, &readData);

      Serial.print("Motor controller 4 diag reg: ");
      Serial.println(readData);

      motorController5.readRegister(0, &readData);

      Serial.print("Motor controller 5 status reg: ");
      Serial.println(readData);

      motorController5.readRegister(1, &readData);

      Serial.print("Motor controller 5 diag reg: ");
      Serial.println(readData);
    }

    if(myControllers[0]->b()) {
      uint8_t readData = 0;

      motorController0.writeRegister(4, 0x80, &readData);
      motorController1.writeRegister(4, 0x80, &readData);
      motorController2.writeRegister(4, 0x80, &readData);
      motorController3.writeRegister(4, 0x80, &readData);
      motorController4.writeRegister(4, 0x80, &readData);
      motorController5.writeRegister(4, 0x80, &readData);
    }
  }

  delay(10);

  // uint8_t readData = 0;
  // motorController0.readRegister(2, &readData);

  // Serial.print("Motor controller 0 IC1 reg: ");
  // Serial.println(readData);
}

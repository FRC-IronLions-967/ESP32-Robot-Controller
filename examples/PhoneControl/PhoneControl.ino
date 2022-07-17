#include <CustomBoardPinDefs.h>
#include <MotorController.h>
#include <SparkController.h>
//#include <GameController.h>

#include <BluetoothController.h>

using namespace team967;
using namespace cpre186;

MotorController leftController(PCB_GPIO_0, 0);
MotorController rightController(PCB_GPIO_1, 1);

SparkController lowerRoller(PCB_GPIO_3, PCB_GPIO_2);
SparkController upperRoller(PCB_GPIO_5, PCB_GPIO_4);

//GameController gameController("99:66:77:00:00:01");

BluetoothController& controller = BluetoothController::createInstance("ESP32test");

void setup() {
  Serial.begin(115200);

  leftController.begin();
  rightController.begin();

  leftController.setInverted(false);
  rightController.setInverted(true);

  lowerRoller.begin();
  upperRoller.begin();

  pinMode(PCB_GPIO_6, INPUT);
  pinMode(ESP32_ONBOARD_LED, OUTPUT);

//  gameController.begin();
  controller.begin();

//  while(!gameController.isConnected()) {
//    Serial.println("Waiting for controller connection...");
//    delay(3000);
//  }

//  Serial.println("Successfully connected to game controller");

}

void loop() {
//  if(controller.isConnected()) {
    digitalWrite(ESP32_ONBOARD_LED, HIGH);
    
//    short leftPower = gameController.getLeftStickY() - gameController.getRightStickX();
//    short rightPower = gameController.getLeftStickY() + gameController.getRightStickX();
    short leftPower = controller.getJoystickY(0) - controller.getJoystickX(1);
    short rightPower = controller.getJoystickY(0) + controller.getJoystickX(1);

    Serial.print(leftPower);
    Serial.print("\t");
    Serial.println(rightPower);

    if(digitalRead(PCB_GPIO_6) == HIGH) {
      leftPower *= 3;
      rightPower *= 3;
      leftPower >>= 2;
      rightPower >>= 2;
    } else {
      leftPower >>= 1;
      rightPower >>= 1;
    }

    // not sure if this is necessary, but check to make sure we haven't exceeded the range on an 8 bit signed int
    leftPower = (leftPower > 127) ? 127 : leftPower;
    leftPower = (leftPower < -128) ? -128 : leftPower;
    rightPower = (rightPower > 127) ? 127 : rightPower;
    rightPower = (rightPower < -128) ? -128 : rightPower;

    leftController.set(leftPower);
    rightController.set(rightPower);

    // fire if right trigger pressed
    if(controller.isPressed(0)) {
      lowerRoller.reverse();
      upperRoller.forward();
    } else if(controller.isPressed(1)) {
      lowerRoller.reverse();
      upperRoller.reverse();
    } else {
      lowerRoller.coast();
      upperRoller.coast();
    }
//  } else {
//    digitalWrite(ESP32_ONBOARD_LED, LOW);
//    
//    leftController.set(0);
//    rightController.set(0);
//
//    lowerRoller.coast();
//    upperRoller.coast();
//  }

}

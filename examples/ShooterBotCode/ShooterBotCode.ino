#include <CustomBoardPinDefs.h>
#include <MotorController.h>
#include <SparkController.h>
#include <GameController.h>

using namespace team967;

MotorController leftController(PCB_GPIO_0, 0);
MotorController rightController(PCB_GPIO_1, 1);

SparkController lowerRoller(PCB_GPIO_3, PCB_GPIO_2);
SparkController upperRoller(PCB_GPIO_5, PCB_GPIO_4);

GameController gameController("00:22:44:66:88:aa");

void setup() {
  Serial.begin(115200);

  leftController.begin();
  rightController.begin();

  leftController.setInverted(false);
  rightController.setInverted(true);

  lowerRoller.begin();
  upperRoller.begin();

  gameController.begin();

  while(!gameController.isConnected()) {
    Serial.println("Waiting for controller connection...");
    delay(3000);
  }

  Serial.println("Successfully connected to game controller");

}

void loop() {
  if(gameController.isConnected()) {
    short leftPower = gameController.getLeftStickY() - gameController.getRightStickX();
    short rightPower = gameController.getLeftStickY() + gameController.getRightStickX();

    // not sure if this is necessary, but check to make sure we haven't exceeded the range on an 8 bit signed int
    leftPower = (leftPower > 127) ? 127 : leftPower;
    leftPower = (leftPower < -128) ? -128 : leftPower;
    rightPower = (rightPower > 127) ? 127 : rightPower;
    rightPower = (rightPower < -128) ? -128 : rightPower;

    leftController.set(leftPower);
    rightController.set(rightPower);

    // fire if right trigger pressed
    if(gameController.isButtonPressed(RIGHT_TRIGGER)) {
      lowerRoller.reverse();
      upperRoller.forward();
    } else if(gameController.isButtonPressed(LEFT_TRIGGER)) {
      lowerRoller.reverse();
      upperRoller.reverse();
    } else {
      lowerRoller.coast();
      upperRoller.coast();
    }
  } else {
    leftController.set(0);
    rightController.set(0);

    lowerRoller.coast();
    upperRoller.coast();
  }

}

#include <GameController.h>
#include <MotorController.h>
#include <PWMServo.h>

using namespace team967;

MotorController leftController(15, 0);
MotorController rightController(16, 1);
MotorController arm(4, 4);
PWMServo grabber(5, 3);

GameController gameController("00:22:44:66:88:aa");

void setup() {
  Serial.begin(115200);

  leftController.begin();
  rightController.begin();
  arm.begin();
  grabber.begin();

  leftController.setInverted(true);
  rightController.setInverted(false);
  arm.setInverted(true);

  gameController.begin();

  while(!gameController.isConnected()) {
    Serial.println("Waiting for controller connection...");
    delay(3000);
  }

  Serial.println("Successfully connected to game controller");

}

void loop() {
  if(gameController.isConnected()) {
    short leftPower = gameController.getLeftStickY() + gameController.getRightStickX();
    short rightPower = gameController.getLeftStickY() - gameController.getRightStickX();

    // not sure if this is necessary, but check to make sure we haven't exceeded the range on an 8 bit signed int
    leftPower = (leftPower > 127) ? 127 : leftPower;
    leftPower = (leftPower < -128) ? -128 : leftPower;
    rightPower = (rightPower > 127) ? 127 : rightPower;
    rightPower = (rightPower < -128) ? -128 : rightPower;

    leftController.set(leftPower);
    rightController.set(rightPower);

    if(gameController.isButtonPressed(D_UP)) {
      arm.set(20);
    } else if(gameController.isButtonPressed(D_DOWN)) {
      arm.set(-20);
    } else {
      arm.set(0);
    }

    if(gameController.isButtonPressed(RIGHT_BUMP)) {
      grabber.setAngleDegrees(45);
    } else if(gameController.isButtonPressed(LEFT_BUMP)) {
      grabber.setAngleDegrees(-45);
    }
    
  } else {
    leftController.set(0);
    rightController.set(0);
    arm.set(0);
    grabber.setAngleDegrees(0);
  }

}

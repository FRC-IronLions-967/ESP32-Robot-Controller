#include <CustomBoardPinDefs.h>
#include <MotorController.h>
#include <BluetoothGameController.h>

using namespace team967;

MotorController leftController(PCB_GPIO_0, 0);
MotorController rightController(PCB_GPIO_1, 1);

BluetoothGameController gameController("00:22:44:66:88:aa");

void setup() {
  Serial.begin(115200);

  leftController.begin();
  rightController.begin();

  leftController.setInverted(true);
  rightController.setInverted(false);

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
  } else {
    leftController.set(0);
    rightController.set(0);
  }

}

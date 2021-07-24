#include <CustomBoardPinDefs.h>
#include <GameController.h>
#include <MotorController.h>
#include <PWMServo.h>

using namespace team967;

MotorController leftController(PCB_GPIO_0, 0);
MotorController rightController(PCB_GPIO_1, 1);
MotorController arm(PCB_GPIO_2, 4);
PWMServo grabber(PCB_GPIO_3, 3);

GameController gameController("00:22:44:66:88:aa");

const int8_t driveLookup[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18,
                              18, 19, 19, 20, 20, 21, 21, 22, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 34, 35, 37, 38, 40, 41,
                              43, 44, 46, 47, 49, 50, 52, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80, 82, 83, 85, 86, 88, 89,
                              91, 92, 94, 95, 97, 98, 100, 101, 103, 104, 106, 107, 109, 110, 112, 113, 115, 116, 118, 119, 121, 122, 124, 125, 127, 127, 127,
                              127, 127};

const int8_t turnLookup[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18,
                              18, 19, 19, 20, 20, 21, 21, 22, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 34, 35, 37, 38, 40, 41,
                              43, 44, 46, 47, 49, 50, 52, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80, 82, 83, 85, 86, 88, 89,
                              91, 92, 94, 95, 97, 98, 100, 101, 103, 104, 106, 107, 109, 110, 112, 113, 115, 116, 118, 119, 121, 122, 124, 125, 127, 127, 127,
                              127, 127};

void setup() {
  Serial.begin(115200);

  leftController.begin();
  rightController.begin();
  arm.begin();
  grabber.begin();

  leftController.setInverted(false);
  rightController.setInverted(true);
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
    short leftPower = ((-gameController.getLeftStickY() > 0) ? driveLookup[-gameController.getLeftStickY()] : -driveLookup[gameController.getLeftStickY()]) - 
                      ((gameController.getRightStickX() > 0) ? turnLookup[gameController.getRightStickX()] : -turnLookup[-gameController.getRightStickX()]);
    short rightPower = ((-gameController.getLeftStickY() > 0) ? driveLookup[-gameController.getLeftStickY()] : -driveLookup[gameController.getLeftStickY()]) + 
                      ((gameController.getRightStickX() > 0) ? turnLookup[gameController.getRightStickX()] : -turnLookup[-gameController.getRightStickX()]);

    Serial.print("Left Power: ");
    Serial.print(leftPower);
    Serial.print(" Right Power: ");
    Serial.println(rightPower);

    // not sure if this is necessary, but check to make sure we haven't exceeded the range on an 8 bit signed int
    leftPower = (leftPower > 127) ? 127 : leftPower;
    leftPower = (leftPower < -128) ? -128 : leftPower;
    rightPower = (rightPower > 127) ? 127 : rightPower;
    rightPower = (rightPower < -128) ? -128 : rightPower;

    leftController.set(leftPower);
    rightController.set(rightPower);

    if(gameController.isButtonPressed(D_UP)) {
      arm.set(40);
    } else if(gameController.isButtonPressed(D_DOWN)) {
      arm.set(-40);
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

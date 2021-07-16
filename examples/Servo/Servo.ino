#include <CustomBoardPinDefs.h>
#include <PWMServo.h>

using namespace team967;

PWMServo servo(PCB_GPIO_0, 0);

void setup() {
  servo.begin();

}

void loop() {
  servo.setAngleDegrees(90);
  delay(5000);
  servo.setAngleDegrees(0);
  delay(5000);
  servo.setAngleDegrees(-90);
  delay(5000);

}

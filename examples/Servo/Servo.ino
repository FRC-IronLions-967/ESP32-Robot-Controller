#include <PWMServo.h>

using namespace team967;

PWMServo servo(15, 0);

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

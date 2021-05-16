#include <MotorController.h>

MotorController controller(15, 0);

void setup() {
  controller.begin();

}

void loop() {
  for(int i = 0; i < 32768; i++) {
    controller.set(i);
    delay(1);
  }

  for(int i = 32767; i > -32768; i--) {
    controller.set(i);
    delay(1);
  }

  for(int i = -32767; i < 0; i++) {
    controller.set(i);
    delay(1);
  }

}

#include <inputs/GameController.h>
#include <motors/MotorController.h>

using namespace team967;

// Motor Controller objects, the 1st parameter in the constructor is the pin number that will be used for the PWM signal
// the second parameter is the PWM channel to be used, can be a number between 1 and 16
MotorController leftController(15, 0);
MotorController rightController(16, 1);

// Game controller to be used, the string passed is the MAC you set with the SixaxisPairTool
GameController gameController("00:22:44:66:88:aa");

void setup() {
  // start serial output, not necessary but can be helpful to see if the controller is working
  Serial.begin(115200);
  
  leftController.begin();
  rightController.begin();

  leftController.setInverted(false);
  rightController.setInverted(true);

  gameController.begin();

  while(!gameController.isConnected()) {
    Serial.println("Waiting for controller connection...");
    delay(3000);
  }

  Serial.println("Successfully connected to game controller");

}

void loop() {
  leftController.set(gameController.getLeftStickY());
  rightController.set(gameController.getRightStickY());

}

#include <MotorController.h>
#include <GameController.h>

MotorController controller0(15, 0);
MotorController controller1(16, 1);

GameController gameController("00:22:44:66:88:aa");

void setup() {
  Serial.begin(115200);
  
  controller0.begin();
  controller1.begin();

  gameController.begin();

  while(!gameController.isConnected()) {
    Serial.println("Waiting for connection to game controller...");
    delay(5000);
  }

  Serial.println("Connected to game controller");

//  Ps3.begin("00:22:44:66:88:aa");
//
//  while(!Ps3.isConnected()) {
//    Serial.println("Waiting for connection...");
//    delay(5000);
//  }
//
//  Serial.println("Connected to controller");
  
}

void loop() {

  // This code tests the motor controller output
//  for(int i = 0; i < 32768; i++) {
//    controller0.set(i);
//    controller1.set(i);
//    delay(1);
//  }
//
//  for(int i = 32767; i > -32768; i--) {
//    controller0.set(i);
//    controller1.set(i);
//    delay(1);
//  }
//
//  for(int i = -32767; i < 0; i++) {
//    controller0.set(i);
//    controller1.set(i);
//    delay(1);
//  }

//    controller1.set(Ps3.data.analog.stick.ly * 256);
//    Serial.println(Ps3.data.analog.stick.ly * 256, DEC);
//
//    controller0.set(Ps3.data.analog.stick.ry * -256);
//    Serial.println(Ps3.data.analog.stick.ry * -256, DEC);

  for(int i = 0; i < 17; i++) {
    Serial.print("Button ");
    Serial.print(i);
    Serial.print(" state: ");
    Serial.print((gameController.isButtonPressed(i)) ? "true " : "false ");
  }

  Serial.println();
  
  Serial.print("Right X axis: ");
  Serial.print(gameController.getRightStickX());
  Serial.print(" Right Y axis: ");
  Serial.print(gameController.getRightStickY());
  Serial.print(" Left X axis: ");
  Serial.print(gameController.getLeftStickX());
  Serial.print(" Left Y axis: ");
  Serial.print(gameController.getLeftStickY());

  Serial.println();

  Serial.print("Battery state: ");
  Serial.print(gameController.getBattery());
  Serial.println();

  delay(1000);
}

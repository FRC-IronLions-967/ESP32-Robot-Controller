#include <Arduino.h>
#include <Bluepad32.h>

#include <ESP32S3Rev1BoardPinDefs.h>

#include <DRV8873MotorController.h>
#include <ESP32S3LegacyMCPWMChannel.h>
#include <ESP32S3SPIMaster.h>
#include <GameController.h>
#include <PWMServo.h>

using namespace team967;

// this is the object that manages the Bluetooth gamepad
GameController* controller;

// these are PWM channels that are responsible for controlling the motors
ESP32S3LegacyMCPWMChannel mcpwmChannel0(0, 0, MOTOR_CONTROLLER_0_IN1_PIN, MOTOR_CONTROLLER_0_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel1(0, 1, MOTOR_CONTROLLER_1_IN1_PIN, MOTOR_CONTROLLER_1_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel2(0, 2, MOTOR_CONTROLLER_2_IN1_PIN, MOTOR_CONTROLLER_2_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel3(1, 0, MOTOR_CONTROLLER_3_IN1_PIN, MOTOR_CONTROLLER_3_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);

// these are SPI objects that allow the ESP32S3 to read and write registers on the motor controllers
ESP32S3SPIMaster motorControllerSPI0(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_0_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI1(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_1_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI2(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_2_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI3(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_3_PIN, SPI_FREQUENCY);

// these are the two motor objects, 0 controls the left motor and 1 controls the right
DRV8873MotorController motorController0(&mcpwmChannel0, &motorControllerSPI0);
DRV8873MotorController motorController1(&mcpwmChannel1, &motorControllerSPI1);
DRV8873MotorController motorController2(&mcpwmChannel2, &motorControllerSPI2);
DRV8873MotorController motorController3(&mcpwmChannel3, &motorControllerSPI3);

void setup() {
  Serial.begin(115200);

  while(!Serial);

  delay(2000);

  // this sets up the motor controllers and configures them with the appropriate settings
  motorController0.begin();
  motorController1.begin();
  motorController2.begin();
  motorController3.begin();

  motorController0.setInverted(true);
  motorController1.setInverted(false);
  motorController2.setInverted(false);
  motorController3.setInverted(false);

  // this starts the Bluetooth to listen for game controller connections
  GameController::begin();

  // wait for a connection to a game controller
  controller = GameController::waitForConnection();
}

void loop() {
  // update the current state of the gamepad, this must be called or otherwise no updates will happen
  GameController::update();

  // if the controller is connected, grab the latest values and set them on the motors
  // if the controller is disconnected, set outputs to 0 for safety
  if(controller->get()->isConnected()) {
    motorController0.setPower(controller->get()->axisY());
    motorController1.setPower(controller->get()->axisRY());

    if(controller->get()->a()) {
      motorController2.setPower(-controller->get()->brake() / 2); // divide by 2 because Bluepad32 returns a 10 bit unsigned for this (as opposed to signed for others)
    } else {
      motorController2.setPower(controller->get()->brake() / 2);
    }

    // TODO implement your own design for the other roller
  } else {
    motorController0.setPower(0);
    motorController1.setPower(0);
    motorController2.setPower(0);
    motorController3.setPower(0);
  }
}

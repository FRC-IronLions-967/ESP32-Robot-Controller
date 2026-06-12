#include <Arduino.h>
#include <Bluepad32.h>

#include <ESP32S3Rev1BoardPinDefs.h>

#include <DRV8873MotorController.h>
#include <ESP32S3LegacyMCPWMChannel.h>
#include <ESP32S3SPIMaster.h>
#include <GameController.h>
#include <PWMServo.h>

using namespace team967;

GameController* controller;

ESP32S3LegacyMCPWMChannel mcpwmChannel0(0, 0, MOTOR_CONTROLLER_0_IN1_PIN, MOTOR_CONTROLLER_0_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel1(0, 1, MOTOR_CONTROLLER_1_IN1_PIN, MOTOR_CONTROLLER_1_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel2(0, 2, MOTOR_CONTROLLER_2_IN1_PIN, MOTOR_CONTROLLER_2_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel3(1, 0, MOTOR_CONTROLLER_3_IN1_PIN, MOTOR_CONTROLLER_3_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel4(1, 1, MOTOR_CONTROLLER_4_IN1_PIN, MOTOR_CONTROLLER_4_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);
ESP32S3LegacyMCPWMChannel mcpwmChannel5(1, 2, MOTOR_CONTROLLER_5_IN1_PIN, MOTOR_CONTROLLER_5_IN2_PIN, MOTOR_CONTROLLER_PWM_FREQ, MOTOR_CONTROLLER_RESOLUTION_BITS);

ESP32S3SPIMaster motorControllerSPI0(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_0_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI1(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_1_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI2(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_2_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI3(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_3_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI4(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_4_PIN, SPI_FREQUENCY);
ESP32S3SPIMaster motorControllerSPI5(SPI_SCLK_PIN, SPI_SDO_PIN, SPI_SDI_PIN, SPI_CSN_5_PIN, SPI_FREQUENCY);

DRV8873MotorController motorController0(&mcpwmChannel0, &motorControllerSPI0);
DRV8873MotorController motorController1(&mcpwmChannel1, &motorControllerSPI1);
DRV8873MotorController motorController2(&mcpwmChannel2, &motorControllerSPI2);
DRV8873MotorController motorController3(&mcpwmChannel3, &motorControllerSPI3);
DRV8873MotorController motorController4(&mcpwmChannel4, &motorControllerSPI4);
DRV8873MotorController motorController5(&mcpwmChannel5, &motorControllerSPI5);

PWMServo servo0(GPIO_SERVO_0_PIN, 0, DEFAULT_PWM_FREQ, 14);
PWMServo servo1(GPIO_SERVO_1_PIN, 1, DEFAULT_PWM_FREQ, 14);
PWMServo servo2(GPIO_SERVO_2_PIN, 2, DEFAULT_PWM_FREQ, 14);
PWMServo servo3(GPIO_SERVO_3_PIN, 3, DEFAULT_PWM_FREQ, 14);
PWMServo servo4(GPIO_SERVO_4_PIN, 4, DEFAULT_PWM_FREQ, 14);

void setup() {
  Serial.begin(115200);

  while(!Serial);

  delay(2000);

  Serial.println("Start serial prints in main core");

  motorController0.begin();
  motorController1.begin();
  motorController2.begin();
  motorController3.begin();
  motorController4.begin();
  motorController5.begin();

  servo0.begin();
  servo1.begin();
  servo2.begin();
  servo3.begin();
  servo4.begin();

  GameController::begin();
  
  controller = GameController::waitForConnection();
}

void loop() {
    GameController::update();

    if(controller->get()->isConnected()) {
        motorController0.setPower(controller->get()->axisX());
        motorController1.setPower(controller->get()->axisX());
        motorController2.setPower(controller->get()->axisX());
        motorController3.setPower(controller->get()->axisX());
        motorController4.setPower(controller->get()->axisX());
        motorController5.setPower(controller->get()->axisX());

        servo0.setAngleDegrees(controller->get()->axisRX() / 6);
        servo1.setAngleDegrees(controller->get()->axisRX() / 6);
        servo2.setAngleDegrees(controller->get()->axisRX() / 6);
        servo3.setAngleDegrees(controller->get()->axisRX() / 6);
        servo4.setAngleDegrees(controller->get()->axisRX() / 6);
    }

  delay(10);
}

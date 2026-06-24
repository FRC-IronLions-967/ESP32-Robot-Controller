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

const int STATE_IDLE = 0;
const int STATE_INTAKE = 1;
const int STATE_INTAKE_RAMPDOWN = 2;
const int STATE_SHOOTER_RAMPUP = 3;
const int STATE_SHOOT = 4;
const int STATE_UNJAM = 5;

int state = STATE_IDLE;

int startTime = 0;

const int SHOOTER_SPEEDS[] = {51, 102, 153, 204, 255, 306, 357, 408, 459, 511};

int shooterSpeedIndex = 9;

bool lBumpPrevState = false;
bool rBumpPrevState = true;

const int TRIGGER_THRESH = 256;

const int INTAKE_SPEED = 511;
const int KICKER_SPEED = 511;
const int UNJAM_SPEED = 511;

const int INTAKE_RAMPDOWN_TIME = 500; // in milliseconds
const int SHOOTER_RAMPUP_TIME = 500;

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
    int32_t axisX = controller->get()->axisX();
    int32_t axisY = controller->get()->axisY();

    motorController0.setPower(axisY - axisX);
    motorController1.setPower(axisY + axisX);

    if(!lBumpPrevState && controller->get()->topLeft()) {
      if(shooterSpeedIndex > 0) shooterSpeedIndex--;
    }

    if(!rBumpPrevState && controller->get()->topRight()) {
      if(shooterSpeedIndex < 9) shooterSpeedIndex++;
    }

    lBumpPrevState = controller->get()->topLeft();
    rBumpPrevState = controller->get()->topRight();

    int nextState;

    switch(state) {
      case STATE_IDLE:
        motorController2.setPower(0);
        motorController3.setPower(0);

        if(controller->get()->brake() > TRIGGER_THRESH) {
          nextState = STATE_INTAKE;
        } else if(controller->get()->throttle() > TRIGGER_THRESH) {
          nextState = STATE_SHOOTER_RAMPUP;

          startTime = millis();
        } else if(controller->get()->a()) {
          nextState = STATE_UNJAM;
        }
        break;

      case STATE_INTAKE:
        motorController2.setPower(INTAKE_SPEED);
        motorController3.setPower(-INTAKE_SPEED);

        if(controller->get()->brake() < TRIGGER_THRESH) {
          nextState = STATE_INTAKE_RAMPDOWN;

          startTime = millis();
        }
        break;

      case STATE_INTAKE_RAMPDOWN:
        motorController2.setPower(0);
        motorController3.setPower(-INTAKE_SPEED);

        if(millis() - startTime > INTAKE_RAMPDOWN_TIME) {
          nextState = STATE_IDLE;
        }
        break;

      case STATE_SHOOTER_RAMPUP:
        motorController2.setPower(0);
        motorController3.setPower(SHOOTER_SPEEDS[shooterSpeedIndex]);

        if(controller->get()->throttle() < TRIGGER_THRESH) {
          nextState = STATE_IDLE;
        } else if(millis() - startTime > SHOOTER_RAMPUP_TIME) {
          nextState = STATE_SHOOT;
        }
        break;

      case STATE_SHOOT:
        motorController2.setPower(KICKER_SPEED);
        motorController3.setPower(SHOOTER_SPEEDS[shooterSpeedIndex]);

        if(controller->get()->throttle() < TRIGGER_THRESH) {
          nextState = STATE_IDLE;
        }
        break;

      case STATE_UNJAM:
        motorController2.setPower(-UNJAM_SPEED);
        motorController3.setPower(-UNJAM_SPEED);

        if(!controller->get()->a()) {
          nextState = STATE_IDLE;
        }
        break;

      default:
        nextState = STATE_IDLE;
        break;
    }

    state = nextState;
  } else {
    motorController0.setPower(0);
    motorController1.setPower(0);
    motorController2.setPower(0);
    motorController3.setPower(0);
  }
}

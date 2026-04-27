/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-26-2026

Last Updated: 4-26-2026

This header provides a set of constant definitions for the ESP32S3 Revision 1 board.

**************************************************************************************************************************************/

#ifndef ESP32S3REV1BOARDDEFS_H
#define ESP32S3REV1BOARDDEFS_H

namespace team967 {

    const int MOTOR_CONTROLLER_0_IN1_PIN = 47;
    const int MOTOR_CONTROLLER_0_IN2_PIN = 21;
    const int MOTOR_CONTROLLER_1_IN1_PIN = 14;
    const int MOTOR_CONTROLLER_1_IN2_PIN = 13;
    const int MOTOR_CONTROLLER_2_IN1_PIN = 12;
    const int MOTOR_CONTROLLER_2_IN2_PIN = 11;
    const int MOTOR_CONTROLLER_3_IN1_PIN = 10;
    const int MOTOR_CONTROLLER_3_IN2_PIN = 9;
    const int MOTOR_CONTROLLER_4_IN1_PIN = 3;
    const int MOTOR_CONTROLLER_4_IN2_PIN = 8;
    const int MOTOR_CONTROLLER_5_IN1_PIN = 18;
    const int MOTOR_CONTROLLER_5_IN2_PIN = 17;

    const int MOTOR_CONTROLLER_PWM_FREQ = 20000;

    const int MOTOR_CONTROLLER_RESOLUTION_BITS = 9;

    const int NUM_MOTOR_CONTROLLERS = 6;

    const int GPIO_SERVO_PIN_0 = 16;
    const int GPIO_SERVO_PIN_1 = 15;
    const int GPIO_SERVO_PIN_2 = 7;
    const int GPIO_SERVO_PIN_3 = 6;
    const int GPIO_SERVO_PIN_4 = 5;
}

#endif
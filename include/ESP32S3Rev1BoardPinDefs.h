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

    const int MOTOR_CONTROLLER_NFAULT_PIN = 1;

    const int MOTOR_CONTROLLER_PWM_FREQ = 20000;

    const int MOTOR_CONTROLLER_RESOLUTION_BITS = 9;

    const int NUM_MOTOR_CONTROLLERS = 6;

    const int GPIO_SERVO_0_PIN = 16;
    const int GPIO_SERVO_1_PIN = 15;
    const int GPIO_SERVO_2_PIN = 7;
    const int GPIO_SERVO_3_PIN = 6;
    const int GPIO_SERVO_4_PIN = 5;

    const int NUM_GPIO_SERVOS = 5;

    const int SPI_CSN_0_PIN = 42;
    const int SPI_CSN_1_PIN = 41;
    const int SPI_CSN_2_PIN = 40;
    const int SPI_CSN_3_PIN = 36;
    const int SPI_CSN_4_PIN = 35;
    const int SPI_CSN_5_PIN = 48;

    const int SPI_SCLK_PIN = 37;
    const int SPI_SDI_PIN  = 2;
    const int SPI_SDO_PIN  = 39;

    const int SPI_FREQUENCY = 10 * 1000 * 1000; // not yet tested, but defaulting to 10 MHz
    
    const int RGB_LED_PIN = 38;

}

#endif
/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-27-2021

Last Updated: 6-27-2021

This file contains definitions for the various pins on the PCB that is responsible for controlling the robot.  This should make it
easier to write robot code for the various pins without constant references back to the schematics for the PCB

**************************************************************************************************************************************/

#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

// definitions for the current revision of this software
#define CONTROLLER_VERSION_MAJOR  0
#define CONTROLLER_VERSION_MINOR  1
#define CONTROLLER_VERSION_BUGFIX 0

// standard pin definitions for generic use, nothing special here
#define PCB_GPIO_0  23
#define PCB_GPIO_1  22
#define PCB_GPIO_2  21
#define PCB_GPIO_3  32
#define PCB_GPIO_4  19
#define PCB_GPIO_5  33
#define PCB_GPIO_6  18
#define PCB_GPIO_7  25
#define PCB_GPIO_8  26
#define PCB_GPIO_9  17
#define PCB_GPIO_10 27
#define PCB_GPIO_11 16

// definitions for the default I2C pins
#define PCB_I2C_SCL PCB_GPIO_1
#define PCB_I2C_SDA PCB_GPIO_2

// definitions for the default SPI pins
#define PCB_SPI_MOSI PCB_GPIO_0
#define PCB_SPI_MISO PCB_GPIO_4
#define PCB_SPI_CLK  PCB_GPIO_6



#endif
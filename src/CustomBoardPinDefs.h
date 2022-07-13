#ifndef CUSTOMBOARDPINDEFS_H
#define CUSTOMBOARDPINDEFS_H

namespace team967 {

    // definitions for the gpio pins on the custom ESP32 board
    const int PCB_GPIO_0 = 23;
    const int PCB_GPIO_1 = 22;
    const int PCB_GPIO_2 = 21;
    const int PCB_GPIO_3 = 32;
    const int PCB_GPIO_4 = 19;
    const int PCB_GPIO_5 = 33;
    const int PCB_GPIO_6 = 18;
    const int PCB_GPIO_7 = 25;
    const int PCB_GPIO_8 = 26;
    const int PCB_GPIO_9 = 17;
    const int PCB_GPIO_10 = 27;
    const int PCB_GPIO_11 = 16;

    const int ESP32_ONBOARD_LED = 2;

    // definition for the battery monitoring pin
    const int PCB_BATT = 34;

    // definitions for the default I2C pins
    const int PCB_I2C_SCL = PCB_GPIO_1;
    const int PCB_I2C_SDA = PCB_GPIO_2;

    // definitions for the default SPI pins
    const int PCB_SPI_MOSI = PCB_GPIO_0;
    const int PCB_SPI_MISO = PCB_GPIO_4;
    const int PCB_SPI_CLK  = PCB_GPIO_6;

}

#endif
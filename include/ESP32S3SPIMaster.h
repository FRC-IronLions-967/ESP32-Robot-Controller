/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-27-2026

Last Updated: 4-27-2026

This header provides a class that describes a SPI interface for the ESP32S3.

**************************************************************************************************************************************/

#ifndef TEAM967_SPIMASTER_H
#define TEAM967_SPIMASTER_H

#include <stdint.h>

#include <SPIMaster.h>

#include "driver/spi_master.h"

namespace team967 {

    class ESP32S3SPIMaster {

        private:
            spi_device_handle_t spiHandle;
            spi_bus_config_t spiBusConfig;
            spi_device_interface_config_t spiDeviceConfig;
            spi_host_device_t spiHost;
            int csPin;

        public:
            /**
             * Constructor, creates a new ESP32S3SPIMaster object with the given pins.
             * 
             * @param sck SPI clock pin
             * @param mosi SPI master out, slave in pin
             * @param miso SPI master in, slave out pin
             * @param cs SPI chip select pin
             * @param frequency SPI frequency in Hz
             * @param spiHost Which of the hardware SPI controllers to use (defaults to SPI2, but can use others if desired, see Espressif docs)
             * 
             * @return A new ESP32S3SPIMaster object
             */
            ESP32S3SPIMaster(int sck, int mosi, int miso, int cs, int frequency, spi_host_device_t spiHost = SPI2_HOST);

            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            ~ESP32S3SPIMaster();

            /**
             * Initialize the SPI interface.
             * 
             * @return nothing
             */
            void begin(void);

            /**
             * Write a buffer over the SPI interface.
             * 
             * @param data pointer to buffer to be transmitted
             * @param n number of bytes to be transmitted
             * 
             * @return number of bytes written
             */
            uint32_t write(uint8_t* data, uint32_t n);

            /**
             * Read a buffer from the SPI interface.
             * 
             * @param data pointer to buffer to write receive data into
             * @param n number of bytes to read (buffer should be at least this large)
             * 
             * @return number of bytes read
             */
            uint32_t read(uint8_t* data, uint32_t n);

            /**
             * Write and read simultaneously over the SPI interface.
             * 
             * @param txData pointer to transmit buffer
             * @param rxData pointer to receive buffer
             * @param n number of bytes to write and read (both buffers should be at least this large)
             */
            uint32_t writeAndRead(uint8_t* txData, uint8_t* rxData, uint32_t n);

    };

}

#endif
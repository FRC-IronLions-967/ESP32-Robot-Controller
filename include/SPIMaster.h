/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 4-27-2026

Last Updated: 4-27-2026

This header provides a class that describes a generic SPI interface.

**************************************************************************************************************************************/

#ifndef TEAM967_SPIMASTER_H
#define TEAM967_SPIMASTER_H

#include <stdint.h>

namespace team967 {

    class SPIMaster {

        public:
            /**
             * Virtual destructor for class.
             * 
             * @return nothing
             */
            virtual ~SPIMaster() = 0;

            /**
             * Initialize the SPI interface.
             * 
             * @return nothing
             */
            virtual void begin(void) = 0;

            /**
             * Write a buffer over the SPI interface.
             * 
             * @param data pointer to buffer to be transmitted
             * @param n number of bytes to be transmitted
             * 
             * @return number of bytes written
             */
            virtual uint32_t write(uint8_t* data, uint32_t n) = 0;

            /**
             * Read a buffer from the SPI interface.
             * 
             * @param data pointer to buffer to write receive data into
             * @param n number of bytes to read (buffer should be at least this large)
             * 
             * @return number of bytes read
             */
            virtual uint32_t read(uint8_t* data, uint32_t n) = 0;

            /**
             * Write and read simultaneously over the SPI interface.
             * 
             * @param txData pointer to transmit buffer
             * @param rxData pointer to receive buffer
             * @param n number of bytes to write and read (both buffers should be at least this large)
             */
            virtual uint32_t writeAndRead(uint8_t* txData, uint8_t* rxData, uint32_t n) = 0;

    };

}

#endif
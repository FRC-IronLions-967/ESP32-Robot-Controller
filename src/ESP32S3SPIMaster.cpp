#include <ESP32S3SPIMaster.h>

#include <Arduino.h>

team967::ESP32S3SPIMaster::ESP32S3SPIMaster(int sck, int mosi, int miso, int cs, int frequency, spi_host_device_t spiHost) : csPin(cs), spiHost(spiHost) {
    spiBusConfig.sclk_io_num = sck;
    spiBusConfig.mosi_io_num = mosi;
    spiBusConfig.miso_io_num = miso;
    spiBusConfig.quadwp_io_num = -1;
    spiBusConfig.quadhd_io_num = -1;

    spiDeviceConfig.clock_speed_hz = frequency;
    spiDeviceConfig.mode = 1; // CPOL = 0, CPHA = 1
    spiDeviceConfig.spics_io_num = -1; // do software chip select for now (otherwise we are limited to only 3 slaves)
    spiDeviceConfig.queue_size = 1; // keep things simple and only allow one SPI transaction at a time (we aren't doing anything bandwidth intensive)
}

team967::ESP32S3SPIMaster::~ESP32S3SPIMaster() {

}

void team967::ESP32S3SPIMaster::begin(void) {
    pinMode(csPin, OUTPUT);

    digitalWrite(csPin, HIGH); // active low pin so default to high

    esp_err_t ret = spi_bus_initialize(spiHost, &spiBusConfig, SPI_DMA_DISABLED);
    if(ret != ESP_OK && ret != ESP_ERR_INVALID_STATE) {
        _esp_error_check_failed(ret, __FILE__, __LINE__, __ASSERT_FUNC, "");
    }

    ESP_ERROR_CHECK(spi_bus_add_device(spiHost, &spiDeviceConfig, &spiHandle));
}

uint32_t team967::ESP32S3SPIMaster::write(uint8_t* data, uint32_t n) {
    // ESP_ERROR_CHECK(spi_device_acquire_bus(spiHandle, portMAX_DELAY));

    spi_transaction_t trans;
    memset(&trans, 0, sizeof(trans));
    trans.length = n * 8;
    trans.tx_buffer = data;

    digitalWrite(csPin, LOW);
    esp_err_t ret = spi_device_polling_transmit(spiHandle, &trans);
    digitalWrite(csPin, HIGH);

    // spi_device_release_bus(spiHandle);

    return (ret == ESP_OK) ? n : 0;
}

uint32_t team967::ESP32S3SPIMaster::read(uint8_t* data, uint32_t n) {
    // ESP_ERROR_CHECK(spi_device_acquire_bus(spiHandle, portMAX_DELAY));

    spi_transaction_t trans;
    memset(&trans, 0, sizeof(trans));
    trans.flags = SPI_TRANS_USE_TXDATA;
    trans.length = n * 8;
    trans.rx_buffer = data;

    digitalWrite(csPin, LOW);
    esp_err_t ret = spi_device_polling_transmit(spiHandle, &trans);
    digitalWrite(csPin, HIGH);

    // spi_device_release_bus(spiHandle);

    return (ret == ESP_OK) ? n : 0;
}

uint32_t team967::ESP32S3SPIMaster::writeAndRead(uint8_t* txData, uint8_t* rxData, uint32_t n) {
    spi_transaction_t trans;
    memset(&trans, 0, sizeof(trans));
    trans.length = n * 8;
    trans.tx_buffer = txData;
    trans.rx_buffer = rxData;

    digitalWrite(csPin, LOW);
    delayMicroseconds(1);
    esp_err_t ret = spi_device_polling_transmit(spiHandle, &trans);
    delayMicroseconds(1);
    digitalWrite(csPin, HIGH);

    return (ret == ESP_OK) ? n : 0;
}
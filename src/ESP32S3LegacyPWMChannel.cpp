#include <ESP32S3LegacyMCPWMChannel.h>

team967::ESP32S3LegacyMCPWMChannel::ESP32S3LegacyMCPWMChannel(int mcpwmId, int channel, int pin0, int pin1, int frequency, int resolution) :
                                                                MCPWMChannel(mcpwmId, channel, pin0, pin1, frequency, resolution) {
    
    if(mcpwmId == 0) {
        pwmUnit = MCPWM_UNIT_0;
    } else if(mcpwmId == 1) {
        pwmUnit = MCPWM_UNIT_1;
    }

    switch(channel) {

        case 0:
            channelA = MCPWM0A;
            channelB = MCPWM0B;
            timer = MCPWM_TIMER_0;
            break;

        case 1:
            channelA = MCPWM1A;
            channelB = MCPWM1B;
            timer = MCPWM_TIMER_1;
            break;

        case 2:
            channelA = MCPWM2A;
            channelB = MCPWM2B;
            timer = MCPWM_TIMER_2;
            break;

    }
    
    pwmConfig.frequency = frequency;
    pwmConfig.cmpr_a = 0.0f; // default duty cycles both to 0
    pwmConfig.cmpr_b = 0.0f;
    pwmConfig.counter_mode = MCPWM_UP_COUNTER;
    pwmConfig.duty_mode = MCPWM_DUTY_MODE_0; // Active high
}

team967::ESP32S3LegacyMCPWMChannel::~ESP32S3LegacyMCPWMChannel() {

}

void team967::ESP32S3LegacyMCPWMChannel::begin(void) {
    ESP_ERROR_CHECK(mcpwm_gpio_init(pwmUnit, channelA, pin0));
    ESP_ERROR_CHECK(mcpwm_gpio_init(pwmUnit, channelB, pin1));

    ESP_ERROR_CHECK(mcpwm_init(pwmUnit, timer, &pwmConfig));

    ESP_ERROR_CHECK(mcpwm_set_signal_low(pwmUnit, timer, MCPWM_GEN_A));
    ESP_ERROR_CHECK(mcpwm_set_signal_low(pwmUnit, timer, MCPWM_GEN_B));
}

void team967::ESP32S3LegacyMCPWMChannel::forward(uint32_t duty) {
    // duty cycle is (for some reason) a percentage as a float
    float floatDuty = 100.0f * ((float) duty) / ((float) (1 << resolution));

    // IN1 = PWM
    ESP_ERROR_CHECK(mcpwm_set_duty(pwmUnit, timer, MCPWM_GEN_A, floatDuty));
    ESP_ERROR_CHECK(mcpwm_set_duty_type(pwmUnit, timer, MCPWM_GEN_A, MCPWM_DUTY_MODE_0));

    // IN2 = LOW
    ESP_ERROR_CHECK(mcpwm_set_signal_low(pwmUnit, timer, MCPWM_OPR_B));
}

void team967::ESP32S3LegacyMCPWMChannel::reverse(uint32_t duty) {
    // duty cycle is (for some reason) a percentage as a float
    float floatDuty = 100.0f * ((float) duty) / ((float) (1 << resolution));

    // IN2 = PWM
    ESP_ERROR_CHECK(mcpwm_set_duty(pwmUnit, timer, MCPWM_GEN_B, floatDuty));
    ESP_ERROR_CHECK(mcpwm_set_duty_type(pwmUnit, timer, MCPWM_GEN_B, MCPWM_DUTY_MODE_0));

    // IN1 = LOW
    ESP_ERROR_CHECK(mcpwm_set_signal_low(pwmUnit, timer, MCPWM_GEN_A));
}

void team967::ESP32S3LegacyMCPWMChannel::brake(void) {
    ESP_ERROR_CHECK(mcpwm_set_signal_high(pwmUnit, timer, MCPWM_GEN_A));
    ESP_ERROR_CHECK(mcpwm_set_signal_high(pwmUnit, timer, MCPWM_GEN_B));
}

void team967::ESP32S3LegacyMCPWMChannel::coast(void) {
    ESP_ERROR_CHECK(mcpwm_set_signal_low(pwmUnit, timer, MCPWM_GEN_A));
    ESP_ERROR_CHECK(mcpwm_set_signal_low(pwmUnit, timer, MCPWM_GEN_B));
}
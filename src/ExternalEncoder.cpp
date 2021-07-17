/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-19-2021

Last Updated: 6-20-2021

This file provides the definitions of the class methods defined in ExternalEncoder.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include "ExternalEncoder.h"

const uint8_t team967::ExternalEncoder::MAX_ENCODERS = 8;

team967::ExternalEncoder *team967::ExternalEncoder::encoders[MAX_ENCODERS] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
                                                                                nullptr, nullptr};

pcnt_isr_handle_t team967::ExternalEncoder::isrHandle = nullptr;

bool team967::ExternalEncoder::attachedInterrupt = false;

void IRAM_ATTR team967::ExternalEncoder::isrHandler(void *arg) {
    ExternalEncoder *enc;

	uint32_t intrStatus = PCNT.int_st.val;

	for (uint8_t i = 0; i < PCNT_UNIT_MAX; i++) {
		if (intrStatus & (BIT(i))) {
			enc = ExternalEncoder::encoders[i];

            // check if an overflow/underflow occured
            // if it did, take that into account and add it to the running total
			int16_t status = 0;
			if(PCNT.status_unit[i].h_lim_lat){
				status = enc->encConfig.counter_h_lim;
			}
			if(PCNT.status_unit[i].l_lim_lat){
				status = enc->encConfig.counter_l_lim;
			}

            // clear the interrupt
			PCNT.int_clr.val = BIT(i);
            enc->lastUpdate = micros();
            enc->lastValue = enc->getCount();
			enc->setCount(status + enc->getCount());
		}
	}
}

team967::ExternalEncoder::ExternalEncoder(uint8_t pinA, uint8_t pinB, EncoderType type, uint16_t cpr, bool usePullUps) {
    channelA = (gpio_num_t) pinA;
    channelB = (gpio_num_t) pinB;
    encoderType = type;
    clicksPerRotation = cpr;
    pullUps = usePullUps;
    counterId = (pcnt_unit_t) -1;
    count = 0;
    lastUpdate = 0;
}

team967::ExternalEncoder::~ExternalEncoder() {
    pauseCount();
}

bool team967::ExternalEncoder::attach() {
    if(attached) return false;

    // find the first available pulse counter
    uint8_t index;
    for(index = 0; index < MAX_ENCODERS; index++) {
        if(encoders[index] == nullptr) {
            encoders[index] = this;
            break;
        }
    }
    
    // if index is at the maximum, return false since the ESP32 is out of pulse counters
    if(index == MAX_ENCODERS) return false;

    counterId = (pcnt_unit_t) index;
    gpio_pad_select_gpio(channelA);
    gpio_pad_select_gpio(channelB);
    gpio_set_direction(channelA, GPIO_MODE_INPUT);
    gpio_set_direction(channelB, GPIO_MODE_INPUT);
    if(pullUps) {
        gpio_pullup_en(channelA);
        gpio_pullup_en(channelB);
    }

    // Set up encoder PCNT configuration
	encConfig.pulse_gpio_num = channelA;
	encConfig.ctrl_gpio_num = channelB;

    // attach to a counter
	encConfig.unit = counterId;
	encConfig.channel = PCNT_CHANNEL_0;

	encConfig.pos_mode = (encoderType != Single) ? PCNT_COUNT_DEC : PCNT_COUNT_DIS;
	encConfig.neg_mode = PCNT_COUNT_INC;

	encConfig.lctrl_mode = PCNT_MODE_KEEP;
    encConfig.hctrl_mode = PCNT_MODE_REVERSE;

	encConfig.counter_h_lim = 32766;
	encConfig.counter_l_lim = -32766;

	pcnt_unit_config(&encConfig);

    if (encoderType == Full) {
		// set up second channel for full quad
		encConfig.pulse_gpio_num = channelB;
		encConfig.ctrl_gpio_num = channelA;

		encConfig.unit = counterId;
		encConfig.channel = PCNT_CHANNEL_1;

		encConfig.pos_mode = PCNT_COUNT_DEC;
		encConfig.neg_mode = PCNT_COUNT_INC;

		encConfig.lctrl_mode = PCNT_MODE_REVERSE;
		encConfig.hctrl_mode = PCNT_MODE_KEEP;

		encConfig.counter_h_lim = 32766;
		encConfig.counter_l_lim = -32766;

		pcnt_unit_config(&encConfig);
	} else {
        // disable the other channel if in Single mode
		encConfig.pulse_gpio_num = channelB; //make prior control into signal
		encConfig.ctrl_gpio_num = channelA;    //and prior signal into control

		encConfig.unit = counterId;
		encConfig.channel = PCNT_CHANNEL_1;

        // set pulses counting to disabled
		encConfig.pos_mode = PCNT_COUNT_DIS;
		encConfig.neg_mode = PCNT_COUNT_DIS;

		encConfig.lctrl_mode = PCNT_MODE_DISABLE;
		encConfig.hctrl_mode = PCNT_MODE_DISABLE;

		encConfig.counter_h_lim = 32766;
		encConfig.counter_l_lim = -32766;

		pcnt_unit_config(&encConfig);	
	}

    // try to filter out invalid pulses
    setFilter(1<<8);

	pcnt_event_enable(counterId, PCNT_EVT_H_LIM);
	pcnt_event_enable(counterId, PCNT_EVT_L_LIM);

	pcnt_counter_pause(counterId);
	pcnt_counter_clear(counterId);
	
	if(!attachedInterrupt){
		attachedInterrupt = true;
		esp_err_t er = pcnt_isr_register(isrHandler, (void *) NULL, 0, &isrHandle);
		if (er != ESP_OK){
			return false;
		}
        attached = true;
	}
	pcnt_intr_enable(counterId);
	pcnt_counter_resume(counterId);

    return true;
}

void team967::ExternalEncoder::begin() {
    attach();
    clearCount();
}

void team967::ExternalEncoder::setCount(int64_t count) {
    int16_t tmp;
    pcnt_get_counter_value(counterId, &tmp);
    this->count = count - tmp;
}

int64_t team967::ExternalEncoder::getCount() {
    int16_t tmp;
    pcnt_get_counter_value(counterId, &tmp);
    return count + tmp;
}

void team967::ExternalEncoder::clearCount() {
    count = 0;
    pcnt_counter_clear(counterId);
}

void team967::ExternalEncoder::pauseCount() {
    pcnt_counter_pause(counterId);
}

void team967::ExternalEncoder::resumeCount() {
    pcnt_counter_resume(counterId);
}

void team967::ExternalEncoder::setFilter(uint16_t value) {
    if(value > (1<<10) - 1) value = (1<<10) - 1;
	if(value == 0) {
		pcnt_filter_disable(counterId);	
	} else {
		pcnt_set_filter_value(counterId, value);
		pcnt_filter_enable(counterId);
	}
}

uint16_t team967::ExternalEncoder::getCPR() {
    return clicksPerRotation;
}

void team967::ExternalEncoder::setCPR(uint16_t cpr) {
    clicksPerRotation = cpr;
}

double team967::ExternalEncoder::getVelocity() {
    double v = ((double)(getCount() - lastValue)) / ((double)(micros() - lastUpdate)) / clicksPerRotation * 1000000;
    lastUpdate = micros();
    lastValue = getCount();

    return v;
}

int16_t team967::ExternalEncoder::getRotationsInt() {
    return getCount() / clicksPerRotation;
}

int16_t team967::ExternalEncoder::getRotationsRem() {
    return getCount() % clicksPerRotation;
}

double team967::ExternalEncoder::getRotationsDouble() {
    return ((double) getCount()) / ((double) clicksPerRotation);
}
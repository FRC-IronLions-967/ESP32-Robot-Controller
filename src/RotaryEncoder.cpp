/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-19-2021

Last Updated: 6-19-2021

This file provides the definitions of the class methods defined in RotaryEncoder.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t pinA, uint8_t pinB, EncoderType type, uint16_t cpr) {
    channelA = pinA;
    channelB = pinB;
    encoderType = type;
    clicksPerRotation = cpr;
}

RotaryEncoder::~RotaryEncoder() {
    pauseCount();
}

void RotaryEncoder::begin() {
    ESP32Encoder::useInternalWeakPullResistors=UP;

    switch(encoderType) {
        case Single:
            encoder.attachSingleEdge(channelA, channelB);
            break;

        case Half:
            encoder.attachHalfQuad(channelA, channelB);
            break;

        case Full:
            encoder.attachFullQuad(channelA, channelB);
            break;
    }

    encoder.clearCount();
}

void RotaryEncoder::setCount(int64_t count) {
    encoder.setCount(count);
}

int64_t RotaryEncoder::getCount() {
    return encoder.getCount();
}

int64_t RotaryEncoder::clearCount() {
    return encoder.clearCount();
}

int64_t RotaryEncoder::pauseCount() {
    return encoder.pauseCount();
}

int64_t RotaryEncoder::resumeCount() {
    return encoder.resumeCount();
}

void RotaryEncoder::setFilter(uint16_t value) {
    encoder.setFilter(value);
}

uint16_t RotaryEncoder::getCPR() {
    return clicksPerRotation;
}

void RotaryEncoder::setCPR(uint16_t cpr) {
    clicksPerRotation = cpr;
}

uint64_t RotaryEncoder::getRotationsInt() {
    return encoder.getCount() / clicksPerRotation;
}

uint16_t RotaryEncoder::getRotationsRem() {
    return encoder.getCount() % clicksPerRotation;
}

double RotaryEncoder::getRotationsDouble() {
    return ((double) encoder.getCount()) / ((double) clicksPerRotation);
}
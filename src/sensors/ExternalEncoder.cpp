/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-19-2021

Last Updated: 6-20-2021

This file provides the definitions of the class methods defined in ExternalEncoder.h.  Please see that file for more details.

**************************************************************************************************************************************/

#include "ExternalEncoder.h"

team967::ExternalEncoder::ExternalEncoder(uint8_t pinA, uint8_t pinB, EncoderType type, uint16_t cpr) {
    channelA = pinA;
    channelB = pinB;
    encoderType = type;
    clicksPerRotation = cpr;
}

team967::ExternalEncoder::~ExternalEncoder() {
    pauseCount();
}

void team967::ExternalEncoder::begin() {
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

void team967::ExternalEncoder::setCount(int64_t count) {
    encoder.setCount(count);
}

int64_t team967::ExternalEncoder::getCount() {
    return encoder.getCount();
}

int64_t team967::ExternalEncoder::clearCount() {
    return encoder.clearCount();
}

int64_t team967::ExternalEncoder::pauseCount() {
    return encoder.pauseCount();
}

int64_t team967::ExternalEncoder::resumeCount() {
    return encoder.resumeCount();
}

void team967::ExternalEncoder::setFilter(uint16_t value) {
    encoder.setFilter(value);
}

uint16_t team967::ExternalEncoder::getCPR() {
    return clicksPerRotation;
}

void team967::ExternalEncoder::setCPR(uint16_t cpr) {
    clicksPerRotation = cpr;
}

uint64_t team967::ExternalEncoder::getRotationsInt() {
    return encoder.getCount() / clicksPerRotation;
}

uint16_t team967::ExternalEncoder::getRotationsRem() {
    return encoder.getCount() % clicksPerRotation;
}

double team967::ExternalEncoder::getRotationsDouble() {
    return ((double) encoder.getCount()) / ((double) clicksPerRotation);
}
#include "SparkController.h"

team967::SparkController::SparkController(int forwardPin, int reversePin) {
    fPin = forwardPin;
    rPin = reversePin;
}

team967::SparkController::~SparkController() {

}

void team967::SparkController::begin() {
    pinMode(fPin, OUTPUT);
    pinMode(rPin, OUTPUT);

    coast();

    state = COAST;
}

void team967::SparkController::forward() {
    digitalWrite(fPin, HIGH);
    digitalWrite(rPin, LOW);

    state = FORWARD;
}

void team967::SparkController::reverse() {
    digitalWrite(fPin, LOW);
    digitalWrite(rPin, HIGH);

    state = REVERSE;
}

void team967::SparkController::coast() {
    digitalWrite(fPin, LOW);
    digitalWrite(rPin, LOW);

    state = COAST;
}

void team967::SparkController::brake() {
    digitalWrite(fPin, HIGH);
    digitalWrite(rPin, HIGH);

    state = BRAKE;
}

team967::SparkController::State team967::SparkController::getState() {
    return state;
}
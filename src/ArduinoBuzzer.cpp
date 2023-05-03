#include "ArduinoBuzzer.h"

ArduinoBuzzer::ArduinoBuzzer(pin_size_t port) {
    this->_port = port;
}

void ArduinoBuzzer::play(uint16_t frequency) {
    tone(this->_port, frequency);
}

void ArduinoBuzzer::stop() {
    noTone(this->_port);
}
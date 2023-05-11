#include "DigitMultiplexer.h"

DigitMultiplexer::DigitMultiplexer(std::vector<pin_size_t> arduino_ports, bool positive_logic) {
    this->_arduino_ports = arduino_ports;
    this->_positive_logic = positive_logic;
}

void DigitMultiplexer::enable(uint8_t channel) {
    this->disableAll();
    digitalWrite(this->_arduino_ports[channel], this->_positive_logic);
}

void DigitMultiplexer::disableAll() {
    for (auto port : this->_arduino_ports) digitalWrite(port, !this->_positive_logic);
}

uint8_t DigitMultiplexer::getNumChannels() {
    return this->_arduino_ports.size();
}
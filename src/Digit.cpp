#include "Digit.h"

Digit::Digit(std::vector<pin_size_t> arduino_ports) {
    this->_arduino_ports = arduino_ports;
}

void Digit::setValue(uint8_t value) {
    auto values = this->decimalToGPIO(value);
    for (uint8_t n = 0; n < this->_arduino_ports.size(); n++) digitalWrite(this->_arduino_ports[n], values[n]);
}
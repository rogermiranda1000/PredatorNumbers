#pragma once

#include <stdint.h>
#include <vector>
#include <Arduino.h>

class Digit {
protected:
    std::vector<pin_size_t> _arduino_ports;

    virtual std::vector<bool> decimalToGPIO(uint8_t value) = 0;

public:
    Digit(std::vector<pin_size_t> arduino_ports);

    virtual void setValue(uint8_t value);
};
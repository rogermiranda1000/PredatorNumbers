#pragma once

#include <Arduino.h>
#include <vector>
#include "Multiplexer.h"

class DigitMultiplexer : public Multiplexer {
private:
    std::vector<pin_size_t> _arduino_ports;
    bool _positive_logic;

public:
    DigitMultiplexer(std::vector<pin_size_t> arduino_ports, bool positive_logic);

    void enable(uint8_t channel);
    void disableAll();
    uint8_t getNumChannels();
};
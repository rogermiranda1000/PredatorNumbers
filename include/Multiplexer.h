#pragma once

#include <stdint.h>

class Multiplexer {
public:
    virtual void enable(uint8_t channel) = 0;
    virtual void disableAll() = 0;
    virtual uint8_t getNumChannels() = 0;
};
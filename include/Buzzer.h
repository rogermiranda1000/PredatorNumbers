#pragma once

#include <stdint.h>

class Buzzer {
public:
    virtual void play(uint16_t frequency) = 0;
    virtual void stop() = 0;
};
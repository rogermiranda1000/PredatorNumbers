#pragma once

#include <stdint.h>

class Delayable {
public:
    virtual ~Delayable() = default;

    virtual uint16_t getMsUntilNextUpdate(uint32_t tick) = 0;
    virtual uint32_t getMsUntilFinish(uint32_t tick) = 0;
};
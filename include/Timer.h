#pragma once

#include <stdint.h>

class Timer {
public:
    virtual uint32_t getCurrentTime() = 0;
};
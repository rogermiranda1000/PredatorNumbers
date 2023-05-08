#pragma once

#include <stdint.h>

class TimerCounter {
public:
    virtual ~TimerCounter() = default;

    virtual uint32_t getElapsedTime() = 0;
    virtual void resetCounter() = 0;
};
#pragma once

#include <Arduino.h>
#include <functional>
#include "Timer.h"

class LambdaTimer : public Timer {
private:
    std::function<uint32_t()> _lambda;

public:
    LambdaTimer(std::function<uint32_t()> lambda);

    uint32_t getCurrentTime();
};
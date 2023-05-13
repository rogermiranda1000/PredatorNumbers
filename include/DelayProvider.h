#pragma once

#include "Delayable.h"

class DelayProvider : public Delayable {
public:
    ~DelayProvider() = default;

    uint16_t getMsUntilNextUpdate(uint32_t tick);
    uint32_t getMsUntilFinish(uint32_t tick);
};
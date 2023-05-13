#pragma once

#include "TimerTriggered.h"

class CounterState : public TimerTriggered {
public:
    virtual ~CounterState() = default;
};
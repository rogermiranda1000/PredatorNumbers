#pragma once

#include "CounterState.h"

class CounterIsStoppedState : public CounterState {
public:
    ~CounterIsStoppedState() = default;

    void onTimerTriggered(TimerTrigger *trigger) { }
};
#pragma once

#include <stdint.h>
#include "CounterState.h"
#include "NumberingSystem.h"
#include "Counter.h"

class Counter;

class CounterIsPlayingState : public CounterState {
private:
    Counter *_counter;

    static uint16_t getPriorDigit(uint16_t value, NumberingSystem<uint16_t> *ns);

public:
    CounterIsPlayingState(Counter *counter);
    ~CounterIsPlayingState() = default;

    void onTimerTriggered(TimerTrigger *trigger);
};
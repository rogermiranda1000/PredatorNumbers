#pragma once

#include "CounterUpdated.h"
#include "TimerTrigger.h"
#include "Delayable.h"
#include "Counter.h"

class CounterTimerUpdater : public CounterUpdated {
private:
    TimerTrigger *_timer;
    // we don't need the Counter, as the listener already sends the pointer

public:
    CounterTimerUpdater(TimerTrigger *timer);
    ~CounterTimerUpdater();

    void onCounterChange(Counter *counter, uint16_t new_value);
    void onCounterStateChanged(Counter *counter, CounterState *state) {}
};
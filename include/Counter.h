#pragma once

#include <stdint.h>
#include <vector>
#include "CounterUpdated.h"
#include "CounterState.h"
#include "TimerTrigger.h"
#include "TimerTriggered.h"
#include "CounterIsPlayingState.h"
#include "CounterIsStoppedState.h"
#include "Delayable.h"
#include "NumberingSystem.h"

class Counter : public TimerTriggered {
private:
    uint16_t _current;
    std::vector<CounterUpdated*> _listeners;
    CounterState *_state;
    TimerTrigger *_timer;
    Delayable *_delay_provider;
    NumberingSystem<uint16_t> *_numbering_converter;

protected:
    void trigger();

public:
    Counter(Delayable *delay_provider, NumberingSystem<uint16_t> *numbering_converter);
    ~Counter();

    void onTimerTriggered(TimerTrigger *trigger);
    void setCurrent(uint16_t current);
    void play();
    void pause();
    uint16_t getCurrent();
    Delayable *getDelayable();
    NumberingSystem<uint16_t> *getNumberingSystem();
    void addListener(CounterUpdated *listener);
};
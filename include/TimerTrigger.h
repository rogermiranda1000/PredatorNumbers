#pragma once

#include <stdint.h>
#include "TimerTriggered.h"

class TimerTrigger {
protected:
    uint32_t _invoke_every;
    TimerTriggered *_listener;

    void trigger();

public:
    TimerTrigger *setTriggerTime(uint32_t every);

    void setListener(TimerTriggered *listener);
};
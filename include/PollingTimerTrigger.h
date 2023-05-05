#pragma once

#include <stdint.h>
#include "TimerCounter.h"
#include "StatefulClass.h"
#include "TimerTrigger.h"

class PollingTimerTrigger : public TimerTrigger, public StatefulClass {
private:
    TimerCounter *_timer;

public:
    PollingTimerTrigger(TimerCounter *timer);

    TimerTrigger *setTriggerTime(uint32_t every);

    void update();
};
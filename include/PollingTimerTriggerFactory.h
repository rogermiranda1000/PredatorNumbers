#pragma once

#include <functional>
#include "Timer.h"
#include "SubtractTimerCounter.h"
#include "PollingTimerTrigger.h"
#include "TimerTrigger.h"
#include "StatefulClass.h"

class PollingTimerTriggerFactory {
private:
    std::function<void(StatefulClass*)> _add_updateable_element_callback;
    Timer *_timer;


public:
    PollingTimerTriggerFactory(Timer *timer, std::function<void(StatefulClass*)> add_updateable_element_callback);

    TimerTrigger *build();
};
#pragma once

class TimerTrigger;

class TimerTriggered {
public:
    virtual void onTimerTriggered(TimerTrigger *trigger) = 0;
};
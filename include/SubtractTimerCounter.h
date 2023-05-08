#pragma once

#include "Timer.h"
#include "TimerCounter.h"

class SubtractTimerCounter : public TimerCounter {
private:
    uint32_t _last_time;
    Timer *_timer;

public:
    SubtractTimerCounter(Timer *timer);
    ~SubtractTimerCounter() = default;

    /**
     * Gets the time between now and the last time `resetCounter` has been called.
     * If `resetCounter` hasn't been called, or the elapsed time exceeds the timer's max ms count
     * the return will be undefined.
     * @return Elapsed time
     */
    uint32_t getElapsedTime();

    void resetCounter();
};
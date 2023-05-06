#include "PollingTimerTrigger.h"

PollingTimerTrigger::PollingTimerTrigger(TimerCounter *timer) {
    this->_timer = timer;
}

TimerTrigger *PollingTimerTrigger::setTriggerTime(uint32_t every) {
    this->TimerTrigger::setTriggerTime(every);
    this->_timer->resetCounter(); // reset the counter when they change the trigger time
    return this;
}

void PollingTimerTrigger::update() {
    if (this->_timer->getElapsedTime() >= this->_invoke_every) {
        this->_timer->resetCounter();
        this->trigger();
    }
}
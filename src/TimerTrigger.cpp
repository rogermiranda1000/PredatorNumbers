#include "TimerTrigger.h"

void TimerTrigger::setListener(TimerTriggered *listener) {
    this->_listener = listener;
}

void TimerTrigger::trigger() {
    if (this->_listener != nullptr) this->_listener->onTimerTriggered(this);
}

TimerTrigger *TimerTrigger::setTriggerTime(uint32_t every) {
    this->_invoke_every = every;
    return this;
}
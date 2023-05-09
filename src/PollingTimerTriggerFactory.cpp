#include "PollingTimerTriggerFactory.h"

PollingTimerTriggerFactory::PollingTimerTriggerFactory(Timer *timer, std::function<void(StatefulClass*)> add_updateable_element_callback) {
    this->_timer = timer;
    this->_add_updateable_element_callback = add_updateable_element_callback;
}

TimerTrigger *PollingTimerTriggerFactory::build() {
    PollingTimerTrigger *ptt = new PollingTimerTrigger(new SubtractTimerCounter(this->_timer));
    this->_add_updateable_element_callback(ptt);
    return ptt;
}
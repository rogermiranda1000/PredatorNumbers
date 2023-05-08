#include "PollingTimerTriggerBuilder.h"

PollingTimerTriggerBuilder::PollingTimerTriggerBuilder(Timer *timer, std::function<void(StatefulClass*)> add_updateable_element_callback) {
    this->_timer = timer;
    this->_add_updateable_element_callback = add_updateable_element_callback;
}

TimerTrigger *PollingTimerTriggerBuilder::build() {
    PollingTimerTrigger *ptt = new PollingTimerTrigger(new SubtractTimerCounter(this->_timer));
    this->_add_updateable_element_callback(ptt);
    return ptt;
}
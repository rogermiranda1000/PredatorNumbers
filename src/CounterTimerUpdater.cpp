#include "CounterTimerUpdater.h"

CounterTimerUpdater::CounterTimerUpdater(TimerTrigger *timer) {
    this->_timer = timer;
}

CounterTimerUpdater::~CounterTimerUpdater() {
    delete this->_timer;
}

void CounterTimerUpdater::onCounterChange(Counter *counter, uint16_t new_value) {
    this->_timer->setTriggerTime(counter->getDelayable()->getMsUntilNextUpdate(new_value));
    this->_timer->setListener(counter);
}
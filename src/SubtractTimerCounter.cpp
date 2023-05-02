#include "SubtractTimerCounter.h"

SubtractTimerCounter::SubtractTimerCounter(Timer *timer) {
    this->_timer = timer;
}

uint32_t SubtractTimerCounter::getElapsedTime() {
    return this->_timer->getCurrentTime() - this->_last_time;
}

void SubtractTimerCounter::resetCounter() {
    this->_last_time = this->_timer->getCurrentTime();
}
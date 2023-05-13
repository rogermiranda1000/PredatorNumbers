#include "CounterIsPlayingState.h"

CounterIsPlayingState::CounterIsPlayingState(Counter *counter) {
    this->_counter = counter;
}

void CounterIsPlayingState::onTimerTriggered(TimerTrigger *trigger) {
    uint16_t set = CounterIsPlayingState::getPriorDigit(this->_counter->getCurrent(), this->_counter->getNumberingSystem());

    this->_counter->setCurrent(set);
}

uint16_t CounterIsPlayingState::getPriorDigit(uint16_t value, NumberingSystem<uint16_t> *ns) {
    if (ns->minNumberRepresented() == value) return value; // reached the min
    return value-1;
}
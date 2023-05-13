#include "Counter.h"

Counter::Counter(Delayable *delay_provider, NumberingSystem<uint16_t> *numbering_converter) {
    this->_delay_provider = delay_provider;
    this->_numbering_converter = numbering_converter;

    this->_state = nullptr;
    this->pause();
}

Counter::~Counter() {
    delete this->_delay_provider;
    // TODO what about the numbering_converter?
}

void Counter::onTimerTriggered(TimerTrigger *trigger) {
    if (this->_state == nullptr) return;
    this->_state->onTimerTriggered(trigger);
}

void Counter::setCurrent(uint16_t current) {
    if (this->_current != current) {
        this->_current = current;
        this->trigger();
    }
}

void Counter::play() {
    if (this->_state != nullptr) delete this->_state;

    this->_state = new CounterIsPlayingState(this);

    for (CounterUpdated *lis : this->_listeners) lis->onCounterStateChanged(this, this->_state);
}

void Counter::pause() {
    if (this->_state != nullptr) delete this->_state;

    this->_state = new CounterIsStoppedState();

    for (CounterUpdated *lis : this->_listeners) lis->onCounterStateChanged(this, this->_state);
}

uint16_t Counter::getCurrent() {
    return this->_current;
}

Delayable *Counter::getDelayable() {
    return this->_delay_provider;
}

NumberingSystem<uint16_t> *Counter::getNumberingSystem() {
    return this->_numbering_converter;
}

void Counter::addListener(CounterUpdated *listener) {
    this->_listeners.push_back(listener);
}

void Counter::trigger() {
    for (CounterUpdated *lis : this->_listeners) lis->onCounterChange(this, this->_current);
}
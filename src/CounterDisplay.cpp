#include "CounterDisplay.h"

CounterDisplay::CounterDisplay(Display *display) {
    this->_display = display;
}

void CounterDisplay::onCounterChange(Counter *counter, uint16_t new_value) {
    this->_display->display(new_value);
}

void CounterDisplay::onCounterStateChanged(Counter *counter, CounterState *state) { }
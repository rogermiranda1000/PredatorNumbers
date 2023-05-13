#include "CounterDisplay.h"

CounterDisplay::CounterDisplay(Display *display) {
    this->_display = display;
}

void CounterDisplay::onCounterChange(Counter *counter, uint16_t new_value) {
    uint16_t value = counter->getNumberingSystem()->baseTenToNumbering(new_value);
    while ((int16_t)value == -1) {
        new_value--;
        value = counter->getNumberingSystem()->baseTenToNumbering(new_value);
    }

    this->_display->display(value);
}
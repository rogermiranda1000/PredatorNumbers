#include "DigitSelector.h"

DigitSelector::DigitSelector(Counter *counter, Display *display) {
    this->_counter = counter;
    this->_display = display;
}

void DigitSelector::startSelecting() {
    this->_counter->pause();
}

void DigitSelector::doneSelecting() {
    this->_counter->play();
}
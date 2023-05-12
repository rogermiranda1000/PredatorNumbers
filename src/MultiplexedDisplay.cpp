#include "MultiplexedDisplay.h"


MultiplexedDisplay::MultiplexedDisplay(DisplayToDigits<uint16_t> *converter, std::vector<Digit*> digits, Multiplexer *multiplex_control, TimerTrigger *trigger)
            : Display(converter, digits) {
    this->_multiplex_control = multiplex_control;
    this->_displaying_digit = 0;

    this->_timer = trigger;
    this->_timer->setTriggerTime(MULTIPLEX_MS_TIME)->setListener(this);
}

MultiplexedDisplay::~MultiplexedDisplay() {
    delete this->_timer;
}

void MultiplexedDisplay::display(uint16_t value) {
    Display::display(value);
    this->_digits[0]->setValue(_displaying[this->_displaying_digit]); // as all the digits are the same, you can set one and all will change
}

void MultiplexedDisplay::onTimerTriggered(TimerTrigger *trigger) {
    if (this->numDigits() == 0) return;

    // update the displaying digit
    this->_displaying_digit = (this->_displaying_digit + 1) % this->numDigits();
    this->_multiplex_control->enable(this->_displaying_digit);

    // display the new digit
    this->_digits[0]->setValue(_displaying[this->_displaying_digit]); // as all the digits are the same, you can set one and all will change
}
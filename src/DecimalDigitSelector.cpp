#include "DecimalDigitSelector.h"

DecimalDigitSelector::DecimalDigitSelector(Counter *counter, Display *display, uint8_t num_digits)
                : DigitSelector(counter, display) {
    this->_num_digits = num_digits;
    this->_digits = (uint8_t*)malloc(sizeof(uint8_t)*num_digits);
}

DecimalDigitSelector::~DecimalDigitSelector() {
    free(this->_digits);
}

void DecimalDigitSelector::startSelecting() {
    DigitSelector::startSelecting();
    this->_selecting_index = 0;
    for (uint8_t n = 0; n < this->_num_digits; n++) this->_digits[n] = 0;
    this->setCurrentSelectedValue(0); // update the display
}

void DecimalDigitSelector::setCurrentSelectedValue(uint16_t value) {
    if (this->_num_digits == 0) return;
    this->_digits[this->_selecting_index] = (uint8_t)value;
    this->_display->display(this->joinDigits()); // update the display
}

bool DecimalDigitSelector::selectingLast() {
    return this->_selecting_index+1 >= this->_num_digits;
}

void DecimalDigitSelector::nextSelection() {
    if (this->_num_digits == 0) return; // we can't select next if there's no digits
    this->_selecting_index = (this->_selecting_index+1) % this->_num_digits;
}

void DecimalDigitSelector::doneSelecting() {
    this->_counter->setCurrent(this->_counter->getNumberingSystem()->numberingToBaseTen(this->joinDigits()));

    DigitSelector::doneSelecting();
}

uint16_t DecimalDigitSelector::joinDigits() {
    // we have a predator digit (and it's in base 10)
    uint16_t current = 0;
    for (uint8_t n = 0; n < this->_num_digits; n++) current = (current*10) + this->_digits[n];
    return current;
}
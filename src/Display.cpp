#include "Display.h"

Display::Display(DisplayToDigits<uint16_t> *converter, std::vector<Digit*> digits) {
    this->_converter = converter;
    this->_digits = digits;
    this->_displaying = (uint8_t*)malloc(sizeof(uint8_t)*this->numDigits());
}

Display::~Display() {
    free(this->_displaying);
}

void Display::display(uint16_t value) {
    std::vector<uint16_t> digits = this->_converter->getDigits(value, this->numDigits());
    for (uint8_t n = 0; n < this->numDigits(); n++) {
        this->_displaying[n] = digits[n];
        this->_digits[n]->setValue(this->_displaying[n]);
    }
}

uint8_t Display::numDigits() {
    return this->_digits.size();
}
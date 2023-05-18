#pragma once

#include "DigitSelector.h"

class DecimalDigitSelector : public DigitSelector {
private:
    uint8_t _num_digits;
    uint8_t *_digits;
    uint8_t _selecting_index;

    uint16_t joinDigits();

public:
    DecimalDigitSelector(Counter *counter, Display *display, uint8_t num_digits);
    ~DecimalDigitSelector();

    void startSelecting();
    void setCurrentSelectedValue(uint16_t value);
    void nextSelection();
    bool selectingLast();
    void doneSelecting();
};
#pragma once

#include <stdint.h>
#include <vector>
#include <stdlib.h>
#include "DisplayToDigits.h"
#include "Digit.h"

class Display {
private:
    DisplayToDigits<uint16_t> *_converter;

protected:
    std::vector<Digit*> _digits;
    uint8_t *_displaying;

public:
    Display(DisplayToDigits<uint16_t> *converter, std::vector<Digit*> digits);
    ~Display();

    void display(uint16_t value);
    uint8_t numDigits();
};
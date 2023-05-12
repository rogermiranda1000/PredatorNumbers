#pragma once

#include <stdint.h>
#include <vector>

template <class T>
class DisplayToDigits {
public:
    virtual std::vector<uint8_t> getDigits(T value, uint8_t num_digits) = 0;
};
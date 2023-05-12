#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <string> // to_string
#include "Arduino.h" // PROGMEM
#include "NumberingSystem.h"
#include "DisplayToDigits.h"

class PredatorNumberingSystem : public NumberingSystem<uint16_t>, public DisplayToDigits<uint16_t> {
public:
    uint16_t numberingToBaseTen(uint16_t number);
    uint16_t maxNumberRepresented();
    uint16_t baseTenToNumbering(uint16_t from);
    uint16_t minNumberRepresented();
    std::vector<uint8_t> getDigits(uint16_t value, uint8_t num_digits);
};
#pragma once

#include <vector>
#include "Digit.h"
#include "Multiplexer.h"
#include "DelayableTask.h"

class MultiplexedPredatorDigit : public Digit {
private:
    Multiplexer *_multiplex_control;

protected:
    std::vector<bool> decimalToGPIO(uint8_t value);

public:
    MultiplexedPredatorDigit(Multiplexer *multiplex_control, std::vector<pin_size_t> arduino_ports);

    void setValue(uint8_t value) override;
};
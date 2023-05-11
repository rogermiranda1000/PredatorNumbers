#pragma once

#include <stdint.h>
#include "Multiplexer.h"
#include "Display.h"
#include "TimerTriggered.h"

class MultiplexedDisplay : public Display, public TimerTriggered {
private:
    uint8_t _displaying_digit;
    Multiplexer *_multiplex_control;

public:
    MultiplexedDisplay(DisplayToDigits<uint16_t> *converter, std::vector<Digit*> digits, Multiplexer *multiplex_control);

    void display(uint16_t value);
    void onTimerTriggered(TimerTrigger *trigger);
};
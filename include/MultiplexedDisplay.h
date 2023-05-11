#pragma once

#include <stdint.h>
#include "Multiplexer.h"
#include "Display.h"
#include "TimerTrigger.h"
#include "TimerTriggered.h"

#define MULTIPLEX_MS_TIME 17

class MultiplexedDisplay : public Display, public TimerTriggered {
private:
    uint8_t _displaying_digit;
    Multiplexer *_multiplex_control;
    TimerTrigger *_timer;

public:
    MultiplexedDisplay(DisplayToDigits<uint16_t> *converter, std::vector<Digit*> digits, Multiplexer *multiplex_control, TimerTrigger *trigger);
    ~MultiplexedDisplay();

    void display(uint16_t value);
    void onTimerTriggered(TimerTrigger *trigger);
};
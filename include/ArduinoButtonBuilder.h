#pragma once

#include "Timer.h"
#include "DebouncingPollingButton.h"
#include "SubtractTimerCounter.h"
#include "ArduinoButton.h"

class ArduinoButtonBuilder {
private:
    Timer *_timer;

public:
    ArduinoButtonBuilder(Timer *timer);

    DebouncingPollingButton *build(uint8_t port, bool pressed_logic);
};
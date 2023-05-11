#pragma once

#include "Display.h"
#include "CounterUpdated.h"

class CounterDisplay : public CounterUpdated {
private:
    Display *_display;

public:
    CounterDisplay(Display *display);

    void onCounterChange(Counter *counter, uint16_t new_value);
    void onCounterStateChanged(Counter *counter, CounterState *state);
};
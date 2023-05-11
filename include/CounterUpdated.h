#pragma once

#include <stdint.h>

class Counter;

class CounterState;

class CounterUpdated {
public:
    virtual void onCounterChange(Counter *counter, uint16_t new_value) = 0;
    
    virtual void onCounterStateChanged(Counter *counter, CounterState *state) = 0;
};
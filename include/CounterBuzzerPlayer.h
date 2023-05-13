#pragma once

#include "CounterUpdated.h"
#include "BuzzerPlayer.h"

class CounterBuzzerPlayer : public CounterUpdated {
private:
    BuzzerPlayer *_player;

public:
    CounterBuzzerPlayer(BuzzerPlayer *player);

    void onCounterChange(Counter *counter, uint16_t new_value);
    void onCounterStateChanged(Counter *counter, CounterState *state) {}
};
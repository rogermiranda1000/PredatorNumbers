#pragma once

#include "StatefulClass.h"
#include "WiFiNINA.h"
#include "CounterUpdated.h"
#include "Counter.h"
#include <string>

class Web : public StatefulClass, public CounterUpdated {
private:
    WiFiServer *_server;
    std::string _remaining_time,
                _showing;

    WiFiClient _serving;
    uint8_t _step;

    static std::string secondsToDate(uint16_t seconds);

public:
    Web();
    ~Web();

    void update();

    void onCounterChange(Counter *counter, uint16_t new_value);
    void onCounterStateChanged(Counter *counter, CounterState *state) {}
};
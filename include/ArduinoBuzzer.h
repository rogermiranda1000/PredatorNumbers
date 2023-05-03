#pragma once

#include <Arduino.h>
#include "Buzzer.h"

class ArduinoBuzzer : public Buzzer {
private:
    pin_size_t _port;

public:
    ArduinoBuzzer(pin_size_t port);

    void play(uint16_t frequency);
    void stop();
};
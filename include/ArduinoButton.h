#pragma once

#include <Arduino.h>
#include "DebouncingPollingButton.h"

class ArduinoButton : public DebouncingPollingButton {
private:
    pin_size_t _arduino_port;
    bool _pressed_logic;

protected:
    bool getInternalButtonState();

public:
    /**
     * ArduinoButton constructor
     * @param timer Timer for DebouncingPollingButton
     * @param port The arduino port already setup
     * @param pressed_logic True if the `digitalRead` of `port` needs to be HIGH when
     *                      the button is pressed, false otherwise
     */
    ArduinoButton(TimerCounter *timer, pin_size_t port, bool pressed_logic);
};
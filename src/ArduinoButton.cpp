#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(TimerCounter *timer, uint8_t port, bool pressed_logic) : DebouncingPollingButton(timer) {
    this->_arduino_port = port;
    this->_pressed_logic = pressed_logic;
}

bool ArduinoButton::getInternalButtonState() {
    PinStatus result = digitalRead(this->_arduino_port);
    // this could be simplified as `result == this->_pressed_logic`, but we'll leave it for better understanding
    return (result == PinStatus::HIGH && this->_pressed_logic) || (result == PinStatus::LOW && !this->_pressed_logic);
}
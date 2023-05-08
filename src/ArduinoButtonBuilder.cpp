#include "ArduinoButtonBuilder.h"

ArduinoButtonBuilder::ArduinoButtonBuilder(Timer *timer) {
    this->_timer = timer;
}

DebouncingPollingButton *ArduinoButtonBuilder::build(uint8_t port, bool pressed_logic) {
    return new ArduinoButton(new SubtractTimerCounter(this->_timer), port, pressed_logic);
}
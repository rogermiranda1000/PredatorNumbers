#include "ArduinoButtonFactory.h"

ArduinoButtonFactory::ArduinoButtonFactory(Timer *timer, std::function<void(StatefulClass*)> add_updateable_element_callback) {
    this->_timer = timer;
    this->_add_updateable_element_callback = add_updateable_element_callback;
}

TriggerableButton *ArduinoButtonFactory::build(uint8_t port, bool pressed_logic) {
    TriggerableButton *btn = new ArduinoButton(new SubtractTimerCounter(this->_timer), port, pressed_logic);
    this->_add_updateable_element_callback((DebouncingPollingButton*)btn);
    return btn;
}
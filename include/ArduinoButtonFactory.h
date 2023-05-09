#pragma once

#include "Timer.h"
#include "TriggerableButton.h"
#include "SubtractTimerCounter.h"
#include "ArduinoButton.h"
#include <functional>
#include "StatefulClass.h"
#include "DebouncingPollingButton.h"

class ArduinoButtonFactory {
private:
    std::function<void(StatefulClass*)> _add_updateable_element_callback;
    Timer *_timer;

public:
    ArduinoButtonFactory(Timer *timer, std::function<void(StatefulClass*)> add_updateable_element_callback);

    TriggerableButton *build(uint8_t port, bool pressed_logic);
};
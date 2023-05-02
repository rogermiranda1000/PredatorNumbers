#pragma once

#include <stdint.h>
#include "TriggerableButton.h"
#include "TimerCounter.h"
#include "StatefulClass.h"

#define DEBOUNCE_TIME 17 // 17ms to consider an "on" pulse as btn pressed

class DebouncingPollingButton : public StatefulClass, public TriggerableButton {
private:
    uint8_t _state;
    TimerCounter *_timer;

protected:
    virtual bool getInternalButtonState() = 0;

public:
    DebouncingPollingButton(TimerCounter *timer);

    void update();
    bool getButtonState();
};
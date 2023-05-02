
#include "DebouncingPollingButton.h"

#define OFF_STATE       0
#define MAYBE_ON_STATE  1
#define ON_STATE        2
#define MAYBE_OFF_STATE 3

DebouncingPollingButton::DebouncingPollingButton(TimerCounter *timer) {
    this->_timer = timer;
    this->_state = 0;
}

void DebouncingPollingButton::update() {
    switch (this->_state) {
    case OFF_STATE:
        if (this->getInternalButtonState()) {
            this->_state = MAYBE_ON_STATE;
            this->_timer->resetCounter(); // reset the counter
        }
        break;
    case MAYBE_ON_STATE:
        if (!this->getInternalButtonState()) this->_state = OFF_STATE; // false on
        else {
            // still pressed
            if (this->_timer->getElapsedTime() >= DEBOUNCE_TIME) {
                // enought time to be considered as valid
                this->_state = ON_STATE;

                this->trigger();
            }
        }
        break;
    case ON_STATE:
        if (!this->getInternalButtonState()) {
            this->_state = MAYBE_OFF_STATE;
            this->_timer->resetCounter(); // reset the counter
        }
        break;
    case MAYBE_OFF_STATE:
        if (this->getInternalButtonState()) this->_state = ON_STATE; // false off
        else {
            // still not pressed
            if (this->_timer->getElapsedTime() >= DEBOUNCE_TIME) {
                // enought time to be considered as valid
                this->_state = OFF_STATE;

                this->trigger();
            }
        }
        break;
    }
}

bool DebouncingPollingButton::getButtonState() {
    // we'll consider the "off debounce" as also on, while considering the "maybe on" as off
    return (this->_state == ON_STATE || this->_state == MAYBE_OFF_STATE);
}
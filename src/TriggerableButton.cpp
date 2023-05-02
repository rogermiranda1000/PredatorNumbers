#include "TriggerableButton.h"

void TriggerableButton::trigger() {
    if (this->_on_button_pressed != nullptr) this->_on_button_pressed->onButtonStateChanged(this, this->getButtonState());
}

void TriggerableButton::addListener(ButtonPressedRequest *callback) {
    this->_on_button_pressed = callback;
}
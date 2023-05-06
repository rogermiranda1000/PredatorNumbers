#include "TriggerableButton.h"

TriggerableButton::TriggerableButton() {
    this->_on_button_pressed = nullptr;
}

void TriggerableButton::trigger() {
    if (this->_on_button_pressed != nullptr) this->_on_button_pressed->onButtonStateChanged(this, this->getButtonState());
}

void TriggerableButton::addListener(ButtonPressedRequest *callback) {
    this->_on_button_pressed = callback;
}

void TriggerableButton::addListener(std::function<void(TriggerableButton*,bool)> callback) {
    this->addListener(new LambdaBPR(callback)); // TODO how do we call the destructor in this case?
}
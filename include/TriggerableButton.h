#pragma once

#include <functional>
#include "Button.h"
#include "ButtonPressedRequest.h"
#include "LambdaBPR.h"

class TriggerableButton : public Button {
protected:
    ButtonPressedRequest *_on_button_pressed;

    void trigger();

public:
    TriggerableButton();

    void addListener(ButtonPressedRequest *callback);
    void addListener(std::function<void(TriggerableButton*,bool)> callback);
};
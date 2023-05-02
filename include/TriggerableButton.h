#pragma once

#include "Button.h"
#include "ButtonPressedRequest.h"

class TriggerableButton : public Button {
protected:
    ButtonPressedRequest *_on_button_pressed;

    void trigger();

public:
    void addListener(ButtonPressedRequest *callback);
};
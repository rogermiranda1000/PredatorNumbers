#pragma once

class TriggerableButton;

class ButtonPressedRequest {
public:
    virtual void onButtonStateChanged(TriggerableButton *btn, bool is_pressed) = 0;
};
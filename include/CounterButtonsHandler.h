#pragma once

#include "DigitSelector.h"
#include "BuzzerPlayer.h"
#include "TriggerableButton.h"
#include "ButtonPressedRequest.h"

class CounterButtonsHandler : public ButtonPressedRequest {
private:
    DigitSelector *_digit_selector;
    BuzzerPlayer *_edit_player;
    TriggerableButton *_left_btn;

    // TODO move to state pattern
    bool _started;
    uint8_t _current;

public:
    CounterButtonsHandler(DigitSelector *ds, BuzzerPlayer *player, TriggerableButton *left_btn);

    void onButtonStateChanged(TriggerableButton *btn, bool is_pressed);
    void leftBtnHandler();
    void rightBtnHandler();
};
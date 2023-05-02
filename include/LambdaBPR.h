#pragma once

#include <functional>
#include "ButtonPressedRequest.h"

class LambdaBPR : public ButtonPressedRequest {
private:
    std::function<void(TriggerableButton*,bool)> _lambda;

public:
    LambdaBPR(std::function<void(TriggerableButton*,bool)> lambda);
    
    void onButtonStateChanged(TriggerableButton* btn, bool is_on);
};

#include "LambdaBPR.h"

LambdaBPR::LambdaBPR(std::function<void(TriggerableButton*,bool)> lambda) {
    this->_lambda = lambda;
}

void LambdaBPR::onButtonStateChanged(TriggerableButton* btn, bool is_on) {
    this->_lambda(btn, is_on);
}
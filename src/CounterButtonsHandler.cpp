#include "CounterButtonsHandler.h"

CounterButtonsHandler::CounterButtonsHandler(DigitSelector *ds, BuzzerPlayer *player, TriggerableButton *left_btn) {
    this->_digit_selector = ds;
    this->_edit_player = player;
    this->_left_btn = left_btn;

    this->_started = false;
}

void CounterButtonsHandler::onButtonStateChanged(TriggerableButton *btn, bool is_pressed) {
    if (!is_pressed) return; // we just want press request

    this->_edit_player->play();
    if (btn == this->_left_btn) this->leftBtnHandler();
    else this->rightBtnHandler();
}

void CounterButtonsHandler::leftBtnHandler() {
    if (!this->_started) return;

    this->_current = (this->_current+1) % 10;
    this->_digit_selector->setCurrentSelectedValue(this->_current);
}

void CounterButtonsHandler::rightBtnHandler() {
    this->_current = 0;
    if (!this->_started) {
        this->_digit_selector->startSelecting();
        this->_started = true;
    }
    else {
        if (this->_digit_selector->selectingLast()) {
            this->_digit_selector->doneSelecting();
            this->_started = false;
        }
        else this->_digit_selector->nextSelection();
    }
}
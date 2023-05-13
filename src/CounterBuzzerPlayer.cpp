#include "CounterBuzzerPlayer.h"

CounterBuzzerPlayer::CounterBuzzerPlayer(BuzzerPlayer *player) {
    this->_player = player;
}

void CounterBuzzerPlayer::onCounterChange(Counter *counter, uint16_t new_value) {
    // TODO check if counter is playing or stopped
    this->_player->play();
}
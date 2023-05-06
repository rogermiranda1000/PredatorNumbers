#include "BuzzerPlayer.h"

#define WAITING     0
#define FIRST_PLAY  1

BuzzerPlayer::BuzzerPlayer(Buzzer *player, TimerTrigger *timer, const std::vector<Note> &notes) {
    this->_player = player;
    this->_timer = timer;
    this->_notes = notes;
    
    this->setState(WAITING);
}

BuzzerPlayer::BuzzerPlayer(Buzzer *player, TimerTrigger *timer, const Note * const notes, size_t notes_size) {
    this->_player = player;
    this->_timer = timer;
    for (size_t n = 0; n < notes_size; n++) this->_notes.push_back(notes[n]);

    this->setState(WAITING);
}

void BuzzerPlayer::play() {
    this->setState(FIRST_PLAY);
}

void BuzzerPlayer::setState(uint16_t new_state) {
    if (new_state > this->_notes.size()) new_state = 0; // no more notes; finished

    this->_state = new_state;
    if (this->_state == WAITING) {
        this->_timer->setListener(nullptr); // desubscribe from events
        this->_player->stop();
    }
    else {
        Note to_play = this->_notes[this->_state - 1];

        this->_player->play(to_play.getFrequency());

        this->_timer->setTriggerTime(to_play.getDuration());
        this->_timer->setListener(this);
    }
}

void BuzzerPlayer::onTimerTriggered(TimerTrigger *trigger) {
    if (this->_state == WAITING) return; // not playing
    this->setState(this->_state+1); // play the next note
}
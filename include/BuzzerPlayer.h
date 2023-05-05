#pragma once

#include <stdint.h>
#include <vector>
#include "Note.h"
#include "Buzzer.h"
#include "TimerTrigger.h"
#include "TimerTriggered.h"

class BuzzerPlayer : public TimerTriggered {
private:
    uint16_t _state;
    Buzzer *_player;
    TimerTrigger *_timer;
    std::vector<Note> _notes;

    void setState(uint16_t new_state);

public:
    BuzzerPlayer(Buzzer *player, TimerTrigger *timer, const std::vector<Note> &notes);
    BuzzerPlayer(Buzzer *player, TimerTrigger *timer, const Note * const notes, size_t notes_size);

    void play();
    void onTimerTriggered(TimerTrigger *trigger);
};
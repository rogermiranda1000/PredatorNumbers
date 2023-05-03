#include "Note.h"

Note::Note(uint16_t frequency, uint32_t duration) {
    this->_frequency = frequency;
    this->_duration = duration;
}

uint16_t Note::getFrequency() {
    return this->_frequency;
}

uint32_t Note::getDuration() {
    return this->_duration;
}
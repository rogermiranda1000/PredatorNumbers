#include "MultiplexedPredatorDigit.h"

MultiplexedPredatorDigit::MultiplexedPredatorDigit(Multiplexer *multiplex_control, std::vector<pin_size_t> arduino_ports)
                : Digit(arduino_ports) {
    this->_multiplex_control = multiplex_control;
}

void MultiplexedPredatorDigit::setValue(uint8_t value) {
    // we can't disable it inmediately because `MultiplexedDisplay` will re-launch it after
    if (value == 0) DelayableTask::getInstance()->queue([this](){ this->_multiplex_control->disableAll(); });
    Digit::setValue(value);
}

std::vector<bool> MultiplexedPredatorDigit::decimalToGPIO(uint8_t value) {
    /* //!\\ we'll supose that the constructor input was (in order) PIN_SEG0 to PIN_SEG5 */
    std::vector<bool> r;
    switch (value) {
        case 1:
            r.push_back(false);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(false);
            r.push_back(false);
            break;

        case 2:
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(false);
            break;

        case 3:
            r.push_back(false);
            r.push_back(true);
            r.push_back(false);
            r.push_back(false);
            r.push_back(true);
            r.push_back(false);
            break;

        case 4:
            r.push_back(true);
            r.push_back(true);
            r.push_back(false);
            r.push_back(true);
            r.push_back(true);
            r.push_back(false);
            break;

        case 5:
            r.push_back(false);
            r.push_back(false);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            break;

        case 6:
            r.push_back(true);
            r.push_back(false);
            r.push_back(false);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            break;

        case 7:
            r.push_back(false);
            r.push_back(false);
            r.push_back(true);
            r.push_back(true);
            r.push_back(false);
            r.push_back(true);
            break;

        case 8:
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(false);
            break;

        default: // 9 (or unexpected)
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            r.push_back(true);
            break;
    }
    return r;
}
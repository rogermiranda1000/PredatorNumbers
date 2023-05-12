#include "PredatorDigit.h"

PredatorDigit::PredatorDigit(Multiplexer *multiplex_control, std::vector<pin_size_t> arduino_ports)
                : Digit(arduino_ports) {
    this->_multiplex_control = multiplex_control;
}

void PredatorDigit::setValue(uint8_t value) {
    // we can't disable it inmediately because `MultiplexedDisplay` will re-launch it after
    if (value == 0) DelayableTask::getInstance()->queue([this](){ this->_multiplex_control->disableAll(); });
    Digit::setValue(value);
}

std::vector<bool> PredatorDigit::decimalToGPIO(uint8_t value) {
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
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;

        case 8:
            break;

        case 9:
            break;

        default: // ignore
            break;
    }
    if (r.empty()) for (auto e : this->_arduino_ports) r.push_back(true);
    return r;
}
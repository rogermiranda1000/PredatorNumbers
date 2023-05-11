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
    // TODO
    std::vector<bool> r;
    for (auto e : this->_arduino_ports) r.push_back(true);
    return r;
}
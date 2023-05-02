#include "LambdaTimer.h"


LambdaTimer::LambdaTimer(std::function<uint32_t()> lambda) {
    this->_lambda = lambda;
}

uint32_t LambdaTimer::getCurrentTime() {
    return this->_lambda();
}
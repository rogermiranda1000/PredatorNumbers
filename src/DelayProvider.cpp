#include "DelayProvider.h"

uint16_t DelayProvider::getMsUntilNextUpdate(uint32_t tick) {
    if (tick >= 60) return 1000;
    return 500 + (500*tick)/60;
}

uint32_t DelayProvider::getMsUntilFinish(uint32_t tick) {
    if (tick >= 60) return (45 + (tick - 60))*1000;
    // integral from the avobe function
    return 500*tick + (25*tick*tick)/6;
}
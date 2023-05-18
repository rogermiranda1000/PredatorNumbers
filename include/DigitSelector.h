#pragma once

#include "Counter.h"
#include "Display.h"

class DigitSelector {
protected:
    Counter *_counter;
    Display *_display;

public:
    DigitSelector(Counter *counter, Display *display);

    virtual void startSelecting();

    virtual void setCurrentSelectedValue(uint16_t value) = 0;
    virtual void nextSelection() = 0;
    virtual bool selectingLast() = 0;

    /**
     * Ends the selection; the number should already be loaded into the Counter
     */
    virtual void doneSelecting();
};
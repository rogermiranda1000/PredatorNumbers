#pragma once

template <class T>
class NumberingSystem {
public:
    virtual T numberingToBaseTen(T number) = 0;
    virtual T maxNumberRepresented() = 0;
    virtual T baseTenToNumbering(T from) = 0;
    virtual T minNumberRepresented() = 0;
};
#pragma once

#include "StatefulClass.h"
#include "WiFiNINA.h"

class Web : public StatefulClass {
private:
    WiFiServer *_server;

public:
    Web();
    ~Web();

    void update();
};
#pragma once

#include "StatefulClass.h"
#include <string>

class WifiConnector : public StatefulClass {
public:
    virtual void connect(char *ssid, char *pass) = 0;
    virtual std::string getIP() = 0;
};
#pragma once

#include "Arduino.h"
#include "WiFiNINA.h"
#include "WifiConnector.h"

class WifiNinaConnector : public WifiConnector {
private:
    char *_ssid;
    char *_pass;
    int _status;

public:
    WifiNinaConnector();
    ~WifiNinaConnector();

    void connect(char *ssid, char *pass);
    void update();
    std::string getIP();
};
#include "WifiNinaConnector.h"

WifiNinaConnector::WifiNinaConnector() {
    this->_ssid = nullptr;
    this->_pass = nullptr;
}

WifiNinaConnector::~WifiNinaConnector() {
    free(this->_ssid);
    free(this->_pass);
}

void WifiNinaConnector::connect(char *ssid, char *pass) {
    free(this->_ssid);
    this->_ssid = (char*)malloc(sizeof(char)*(strlen(ssid)+1));
    strcpy(this->_ssid, ssid);
    free(this->_pass);
    this->_pass = (char*)malloc(sizeof(char)*(strlen(pass)+1));
    strcpy(this->_pass, pass);

    this->_status = WL_IDLE_STATUS;
    this->_status = WiFi.begin(this->_ssid, this->_pass);
    delay(400); // for some reason if it inmediately call update it won't connect
}

void WifiNinaConnector::update() {
    if (this->_status != WL_CONNECTED) {
        this->_status = WiFi.begin(this->_ssid, this->_pass);
        return; // let it connect; the next iteration will handle the rest
    }
}

std::string WifiNinaConnector::getIP() {
    if (this->_status != WL_CONNECTED) return "";

    IPAddress ipAddress = WiFi.localIP();
    return std::to_string(ipAddress[0]) + "." +
        std::to_string(ipAddress[1]) + "." +
        std::to_string(ipAddress[2]) + "." +
        std::to_string(ipAddress[3]);
}
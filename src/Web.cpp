#include "Web.h"

Web::Web() {
    this->_server = new WiFiServer(80);
    this->_server->begin();
    this->_step = 0;

    this->_showing = "0000";
    this->_remaining_time = "00:00:00";
}

Web::~Web() {
    delete this->_server;
}

void Web::update() {
  switch (this->_step) {
  case 0:
  default:
    this->_serving = this->_server->available();   // listen for incoming clients
    if (this->_serving) this->_step++;
    break;
  
  case 1:
    if (this->_serving.available()) this->_step++;
    else this->_step--;
    break;

  case 2:
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    this->_serving.println("HTTP/1.1 200 OK");
    this->_step++;
    break;

  case 3:
    this->_serving.println("Content-type:text/html");
    this->_step++;
    break;

  case 4:
    this->_serving.println();
    this->_step++;
    break;

  case 5:
    // the content of the HTTP response follows the header:
    this->_serving.print(this->_showing.c_str());
    this->_step++;
    break;

  case 6:
    // the content of the HTTP response follows the header:
    this->_serving.print("<br>");
    this->_step++;
    break;
    
  case 7:
    // the content of the HTTP response follows the header:
    this->_serving.print(this->_remaining_time.c_str());
    this->_step++;
    break;

  case 8:
    // TODO subscribe & send each update (instead of forcing a refresh)
    this->_serving.print("<meta http-equiv='refresh' content='1' />"); // refresh the page each second
    this->_step++;
    break;

  case 9:
    // The HTTP response ends with another blank line:
    this->_serving.println();
    this->_step++;
    break;
    
  case 10:
    // close the connection
    this->_serving.stop();
    this->_step = 0;
    break;
  }
}

void Web::onCounterChange(Counter *counter, uint16_t new_value) {
  uint16_t seconds_until_finish = counter->getDelayable()->getMsUntilFinish(new_value) / 1000;
  this->_remaining_time = Web::secondsToDate(seconds_until_finish);

  this->_showing = std::to_string(counter->getNumberingSystem()->baseTenToNumbering(new_value));
  while (this->_showing.size() < 4) this->_showing = "0" + this->_showing;
}

std::string Web::secondsToDate(uint16_t seconds) {
  std::string adding, r;

  adding = std::to_string(seconds / 3600);
  seconds -= (seconds / 3600) * 3600;
  if (adding.size() < 2) adding = "0" + adding;
  r = adding + ":";

  adding = std::to_string(seconds / 60);
  seconds -= (seconds / 60) * 60;
  if (adding.size() < 2) adding = "0" + adding;
  r += adding + ":";

  adding = std::to_string(seconds);
  if (adding.size() < 2) adding = "0" + adding;
  r += adding;

  return r;
}
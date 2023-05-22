#include "Web.h"

Web::Web() {
    this->_server = new WiFiServer(80);
    this->_server->begin();

    this->_remaining_time = "00:00:00";
}

Web::~Web() {
    delete this->_server;
}

void Web::update() {
  WiFiClient client = this->_server->available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    // TODO a while inside the loop it's very bad
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there are bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(this->_remaining_time.c_str());
            // TODO subscribe & send each update (instead of forcing a refresh)
            client.print("<meta http-equiv='refresh' content='1' />"); // refresh the page each second

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // here you can check different endpoints with `currentLine`
      }
    }
    // close the connection:
    client.stop();
  }
}

void Web::onCounterChange(Counter *counter, uint16_t new_value) {
  uint16_t seconds_until_finish = counter->getDelayable()->getMsUntilFinish(new_value) / 1000;
  this->_remaining_time = Web::secondsToDate(seconds_until_finish);
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
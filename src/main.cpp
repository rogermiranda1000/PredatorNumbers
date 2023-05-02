#include <Arduino.h>
#include <vector>
#include "LambdaTimer.h"
#include "SubtractTimerCounter.h"
#include "ArduinoButton.h"
#include "StatefulClass.h"
#include "TriggerableButton.h"

#define SERIAL_SPEED 115200

#define PIN_SEG0 7
#define PIN_SEG1 13
#define PIN_SEG2 5
#define PIN_SEG3 4
#define PIN_SEG4 11
#define PIN_SEG5 12

#define PIN_HIDE 8
#define PIN_S0 10
#define PIN_S1 9

#define PIN_BUZZER 6

#define PIN_BTN0 3
#define PIN_BTN1 2

Timer *_default_timer;
TimerCounter *_timer;
std::vector<StatefulClass*> _updateable_elements;

void setup() {
  Serial.begin(SERIAL_SPEED);

  _default_timer = new LambdaTimer([](){ return (uint32_t)millis(); }); // use the default Arduino timer
  _timer = new SubtractTimerCounter(_default_timer);

  pinMode(PIN_BTN0, INPUT_PULLUP);
  ArduinoButton *btn0 = new ArduinoButton(_timer, PIN_BTN0, false);
  _updateable_elements.push_back(btn0);

  pinMode(PIN_BTN1, INPUT_PULLUP);
  ArduinoButton *btn1 = new ArduinoButton(_timer, PIN_BTN1, false);
  _updateable_elements.push_back(btn1);

  // TODO add the btns to `CounterButtonsHandler`

  btn0->addListener([](TriggerableButton *btn, bool is_on){
    Serial.println("btn0 switch state!");
  });
}

void loop() {
  // update all the state machines
  for (StatefulClass *e : _updateable_elements) e->update();
}
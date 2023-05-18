#include <Arduino.h>
#include <vector>
#include <functional>
#include "LambdaTimer.h"
#include "StatefulClass.h"
#include "TriggerableButton.h"
#include "BuzzerPlayer.h"
#include "ArduinoBuzzer.h"
#include "ArduinoButtonFactory.h"
#include "TriggerableButton.h"
#include "PollingTimerTriggerFactory.h"
#include "DelayableTask.h"
#include "MultiplexedDisplay.h"
#include "CounterDisplay.h"
#include "DigitMultiplexer.h"
#include "MultiplexedPredatorDigit.h"
#include "PredatorNumberingSystem.h"
#include "Digit.h"
#include "Counter.h"
#include "DelayProvider.h"
#include "CounterTimerUpdater.h"
#include "CounterBuzzerPlayer.h"
#include "DecimalDigitSelector.h"
#include "CounterButtonsHandler.h"
#include "WifiNinaConnector.h"
#include "arduino_secrets.h"
#include "Web.h"

#define SERIAL_SPEED 115200

#define PIN_SEG0 5
#define PIN_SEG1 6
#define PIN_SEG2 7
#define PIN_SEG3 8
#define PIN_SEG4 9
#define PIN_SEG5 10

#define PIN_EN1 A0
#define PIN_EN2 A1
#define PIN_EN3 A2
#define PIN_EN4 A3

#define PIN_BUZZER 4

#define PIN_BTN0 3
#define PIN_BTN1 2

#define BUZZER_SOUND_ON_TICK { Note(350,100), Note(600,10), Note(350,20), Note(600,10), Note(350,40) }

TimerCounter *_timer;
std::vector<StatefulClass*> _updateable_elements;

WifiConnector *_wifi;
Web *_web;

void setup() {
  Serial.begin(SERIAL_SPEED);

  // TODO create factories to avoid this mess

  Timer *default_timer = new LambdaTimer(millis); // use the default Arduino timer

  auto updateable_elements_appender = [](StatefulClass *e){ _updateable_elements.push_back(e); };
  ArduinoButtonFactory button_builder(default_timer, updateable_elements_appender);
  PollingTimerTriggerFactory trigger_timer_builder(default_timer, updateable_elements_appender);

  DelayableTask::linkInstance(updateable_elements_appender);

  // TODO add the btns to `CounterButtonsHandler`


  PredatorNumberingSystem *pns = new PredatorNumberingSystem();

  std::vector<pin_size_t> multiplexer_ports;
  pinMode(PIN_EN1, OUTPUT);
  multiplexer_ports.push_back(PIN_EN1);
  pinMode(PIN_EN2, OUTPUT);
  multiplexer_ports.push_back(PIN_EN2);
  pinMode(PIN_EN3, OUTPUT);
  multiplexer_ports.push_back(PIN_EN3);
  pinMode(PIN_EN4, OUTPUT);
  multiplexer_ports.push_back(PIN_EN4);
  DigitMultiplexer *multiplexer = new DigitMultiplexer(multiplexer_ports, true);

  std::vector<pin_size_t> digits_ports;
  pinMode(PIN_SEG0, OUTPUT);
  digits_ports.push_back(PIN_SEG0);
  pinMode(PIN_SEG1, OUTPUT);
  digits_ports.push_back(PIN_SEG1);
  pinMode(PIN_SEG2, OUTPUT);
  digits_ports.push_back(PIN_SEG2);
  pinMode(PIN_SEG3, OUTPUT);
  digits_ports.push_back(PIN_SEG3);
  pinMode(PIN_SEG4, OUTPUT);
  digits_ports.push_back(PIN_SEG4);
  pinMode(PIN_SEG5, OUTPUT);
  digits_ports.push_back(PIN_SEG5);
  std::vector<Digit*> digits;
  for (uint8_t n = 0; n < 4; n++) digits.push_back(new MultiplexedPredatorDigit(multiplexer, digits_ports)); // it's all the same digit because it's multiplexed
  MultiplexedDisplay *display = new MultiplexedDisplay(pns, digits, multiplexer, trigger_timer_builder.build());
  display->display(0); // clear the display

  Counter *counter = new Counter(new DelayProvider(), pns);
  counter->addListener(new CounterTimerUpdater(trigger_timer_builder.build())); // TODO move to factory


  CounterDisplay *cd = new CounterDisplay(display);
  counter->addListener(cd);



  pinMode(PIN_BUZZER, OUTPUT);
  ArduinoBuzzer *buzzer = new ArduinoBuzzer(PIN_BUZZER);

  const Note notes[] = BUZZER_SOUND_ON_TICK;
  BuzzerPlayer *_player = new BuzzerPlayer(buzzer, trigger_timer_builder.build(), notes, sizeof(notes)/sizeof(Note));
  
  CounterBuzzerPlayer *cbp = new CounterBuzzerPlayer(_player);
  counter->addListener(cbp);

  DigitSelector *selector = new DecimalDigitSelector(counter, display, 4);
  



  pinMode(PIN_BTN0, INPUT_PULLUP);
  TriggerableButton *btn0 = button_builder.build(PIN_BTN0, false);

  // TODO custom player for the edit sound
  CounterButtonsHandler *cbh = new CounterButtonsHandler(selector, _player, btn0);

  btn0->addListener(cbh);

  pinMode(PIN_BTN1, INPUT_PULLUP);
  TriggerableButton *btn1 = button_builder.build(PIN_BTN1, false);
  btn1->addListener(cbh);


  _wifi = new WifiNinaConnector();
  _wifi->connect(SECRET_SSID, SECRET_PASS);
  _updateable_elements.push_back(_wifi);
  _web = nullptr;
}

void loop() {
  // update all the state machines
  for (StatefulClass *e : _updateable_elements) e->update();

  if (_web == nullptr) {
    // we need to check if the wifi conection was successful
    std::string ip = _wifi->getIP();
    if (!ip.empty()) {
      Serial.print("Connected. ");
      Serial.println(ip.c_str());

      _web = new Web();
      _updateable_elements.push_back(_web);
    }
  }
}
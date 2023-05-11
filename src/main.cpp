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
#include "PredatorDigit.h"
#include "PredatorNumberingSystem.h"
#include "Digit.h"

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
BuzzerPlayer *_player;
std::vector<StatefulClass*> _updateable_elements;

void setup() {
  Serial.begin(SERIAL_SPEED);

  Timer *default_timer = new LambdaTimer(millis); // use the default Arduino timer

  auto updateable_elements_appender = [](StatefulClass *e){ _updateable_elements.push_back(e); };
  ArduinoButtonFactory button_builder(default_timer, updateable_elements_appender);
  PollingTimerTriggerFactory trigger_timer_builder(default_timer, updateable_elements_appender);

  DelayableTask::linkInstance(updateable_elements_appender);

  pinMode(PIN_BTN0, INPUT_PULLUP);
  TriggerableButton *btn0 = button_builder.build(PIN_BTN0, false);

  pinMode(PIN_BTN1, INPUT_PULLUP);
  TriggerableButton *btn1 = button_builder.build(PIN_BTN1, false);

  // TODO add the btns to `CounterButtonsHandler`

  btn0->addListener([](TriggerableButton *btn, bool is_on){
    Serial.println("btn0 switch state!");
  });

  pinMode(PIN_BUZZER, OUTPUT);
  ArduinoBuzzer *buzzer = new ArduinoBuzzer(PIN_BUZZER);

  const Note notes[] = BUZZER_SOUND_ON_TICK;
  _player = new BuzzerPlayer(buzzer, trigger_timer_builder.build(), notes, sizeof(notes)/sizeof(Note));

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

  PredatorNumberingSystem *pns = new PredatorNumberingSystem();
  std::vector<Digit*> digits;
  for (uint8_t n = 0; n < 4; n++) digits.push_back(new PredatorDigit(multiplexer, ));
  MultiplexedDisplay *display = new MultiplexedDisplay(pns, digits, multiplexer);
}

void loop() {
  // update all the state machines
  for (StatefulClass *e : _updateable_elements) e->update();
}
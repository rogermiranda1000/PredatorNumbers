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
#include "TimerTrigger.h"

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

#define BUZZER_SOUND_ON_TICK { Note(350,100), Note(600,10), Note(350,20), Note(600,10), Note(350,40) }

TimerCounter *_timer;
BuzzerPlayer *_player;
std::vector<StatefulClass*> _updateable_elements;

// DEBUG ONLY
class Test : public TimerTriggered {
public:
    Test() {}

    void onTimerTriggered(TimerTrigger *trigger) {
      _player->play();
    }
};

void setup() {
  Serial.begin(SERIAL_SPEED);

  Timer *default_timer = new LambdaTimer(millis); // use the default Arduino timer

  auto updateable_elements_appender = [](StatefulClass *e){ _updateable_elements.push_back(e); };
  ArduinoButtonFactory button_builder(default_timer, updateable_elements_appender);
  PollingTimerTriggerFactory trigger_timer_builder(default_timer, updateable_elements_appender);

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

  TimerTrigger *ptt = trigger_timer_builder.build();
  const Note notes[] = BUZZER_SOUND_ON_TICK;
  _player = new BuzzerPlayer(buzzer, ptt, notes, sizeof(notes)/sizeof(Note));

  // debug
  ptt = trigger_timer_builder.build();
  ptt->setTriggerTime(1000)->setListener(new Test());
}

void loop() {
  // update all the state machines
  for (StatefulClass *e : _updateable_elements) e->update();
}
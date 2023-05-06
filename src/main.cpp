#include <Arduino.h>
#include <vector>
#include <functional>
#include "LambdaTimer.h"
#include "SubtractTimerCounter.h"
#include "ArduinoButton.h"
#include "StatefulClass.h"
#include "TriggerableButton.h"
#include "BuzzerPlayer.h"
#include "ArduinoBuzzer.h"

#include "PollingTimerTrigger.h" // DEBUG ONLY

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

  Timer *_default_timer = new LambdaTimer(millis); // use the default Arduino timer

  pinMode(PIN_BTN0, INPUT_PULLUP);
  ArduinoButton *btn0 = new ArduinoButton(new SubtractTimerCounter(_default_timer), PIN_BTN0, false);
  _updateable_elements.push_back(btn0);

  pinMode(PIN_BTN1, INPUT_PULLUP);
  ArduinoButton *btn1 = new ArduinoButton(new SubtractTimerCounter(_default_timer), PIN_BTN1, false);
  _updateable_elements.push_back(btn1);

  // TODO add the btns to `CounterButtonsHandler`

  btn0->addListener([](TriggerableButton *btn, bool is_on){
    Serial.println("btn0 switch state!");
  });

  pinMode(PIN_BUZZER, OUTPUT);
  ArduinoBuzzer *buzzer = new ArduinoBuzzer(PIN_BUZZER);

  PollingTimerTrigger *ptt = new PollingTimerTrigger(new SubtractTimerCounter(_default_timer));
  _updateable_elements.push_back(ptt);
  const Note notes[] = BUZZER_SOUND_ON_TICK;
  _player = new BuzzerPlayer(buzzer, ptt, notes, sizeof(notes)/sizeof(Note));

  // debug
  ptt = new PollingTimerTrigger(new SubtractTimerCounter(_default_timer));
  _updateable_elements.push_back(ptt);
  ptt->setTriggerTime(1000)->setListener(new Test());
}

void loop() {
  // update all the state machines
  for (StatefulClass *e : _updateable_elements) e->update();
}
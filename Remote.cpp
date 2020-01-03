#pragma once

#include ".\headers\Remote.h"
#include ".\headers\ButtonCode.h"

const int NUM_ACTIVE_BUTTONS = 22;

// Maps / Dictionaries are not ideal for arduino so array search is better
ButtonEventMapping* BUTTON_EVENTS[NUM_ACTIVE_BUTTONS] = {
  new ButtonEventMapping(CH_MINUS, Event::STOP_SLEWING),
  new ButtonEventMapping(CH, Event::STOP_TRACKING),
  new ButtonEventMapping(CH_PLUS, Event::STOP_CAPTURING),

  new ButtonEventMapping(PREV_TRACK, Event::DECREASE_EXPOSURE_TIME),
  new ButtonEventMapping(NEXT_TRACK, Event::INCREASE_EXPOSURE_TIME),
  new ButtonEventMapping(PLAY_PAUSE, Event::START_CAPTURING),

  new ButtonEventMapping(VOL_DOWN, Event::MOTOR_TEST),
  new ButtonEventMapping(VOL_UP, Event::START_SLEWING),
  new ButtonEventMapping(EQ, Event::START_TRACKING),

  new ButtonEventMapping(ZERO, Event::UNKNOWN),
  new ButtonEventMapping(PLUS_100, Event::TOGGLE_BOTTOM_ROW),
  new ButtonEventMapping(PLUS_200, Event::TOGGLE_TOP_ROW),

  new ButtonEventMapping(ONE, Event::UNKNOWN),
  new ButtonEventMapping(TWO, Event::UNKNOWN),
  new ButtonEventMapping(THREE, Event::UNKNOWN),

  new ButtonEventMapping(FOUR, Event::UNKNOWN),
  new ButtonEventMapping(FIVE, Event::UNKNOWN),
  new ButtonEventMapping(SIX, Event::UNKNOWN),

  new ButtonEventMapping(SEVEN, Event::MANUAL_SLEW_ARA),
  new ButtonEventMapping(EIGHT, Event::MANUAL_SLEW_RA),
  new ButtonEventMapping(NINE, Event::UNKNOWN),

  new ButtonEventMapping(BUTTON_HOLD, Event::BUTTON_HELD)
  
};

void Remote::setup() {
    irReceiver.enableIRIn();
}

Event Remote::checkForPress() {
  if (irReceiver.decode(&this->decodedSignal)) {
    // Serial.println(this->_decodedSig.value, HEX);
    unsigned long keyCode = decodedSignal.value;
    Event event = decodeKeyPress(keyCode);
    irReceiver.resume();
    return event;
  }

  return Event::NONE;
}

Event Remote::decodeKeyPress(unsigned long keyCode) {
//  Serial.print("Checking keyCode: ");
//  Serial.println(keyCode);
  for (int i=0; i<NUM_ACTIVE_BUTTONS; i++) {
    if (BUTTON_EVENTS[i]->keyCode == keyCode) {
      Event event = BUTTON_EVENTS[i]->event;
//      Serial.print("Found event index:");
//      Serial.println(i);
//      Serial.print("Corresponds to event: ");
//      Serial.println(int(event));   
      return event;
    }
  }

  return Event::UNKNOWN;
}

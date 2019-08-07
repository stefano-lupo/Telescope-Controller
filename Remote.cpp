#pragma once

#include "Remote.h"
#include "ButtonCode.h"

const int NUM_ACTIVE_BUTTONS = 11;

// Maps / Dictionaries are not ideal for arduino so array search is better
ButtonEventMapping* BUTTON_EVENTS[NUM_ACTIVE_BUTTONS] = {
  new ButtonEventMapping(CH_MINUS, Event::STOP_MOTOR),
  new ButtonEventMapping(CH, Event::CHANGE_MOTOR_DIRECTION),
  new ButtonEventMapping(CH_PLUS, Event::STOP_CAPTURING),

  new ButtonEventMapping(PREV_TRACK, Event::DECREASE_EXPOSURE_TIME),
  new ButtonEventMapping(NEXT_TRACK, Event::INCREASE_EXPOSURE_TIME),
  new ButtonEventMapping(PLAY_PAUSE, Event::START_CAPTURING),

//  new ButtonEventMapping(VOL_DOWN, Event::INCREASE_STEP_RATE),
//  new ButtonEventMapping(VOL_UP, Event::DECREASE_STEP_RATE),
  new ButtonEventMapping(EQ, Event::START_MOTOR),

  new ButtonEventMapping(ZERO, Event::SET_QUARTER_STEP),
  new ButtonEventMapping(PLUS_100, Event::SET_HALF_STEP),
  new ButtonEventMapping(PLUS_200, Event::SET_FULL_STEP),

//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),
//  new ButtonEventMapping(0xFFA25D, Event::DECREASE_EXPOSURE_TIME),

  new ButtonEventMapping(BUTTON_HOLD, Event::BUTTON_HELD)
  
};

void Remote::setup() {
    this->_irRecv.enableIRIn();
}

Event Remote::checkForPress() {
  if (this->_irRecv.decode(&this->_decodedSig)) {
    // Serial.println(this->_decodedSig.value, HEX);
    unsigned long keyCode = _decodedSig.value;
    Event event = this->decodeKeyPress(keyCode);
    this->_irRecv.resume();
    return event;
  }

  return Event::NONE;
}

Event Remote::decodeKeyPress(unsigned long keyCode) {
//  Serial.print("Checking keyCode: ");
//  Serial.println(keyCode);
  for (int i=0; i<NUM_ACTIVE_BUTTONS; i++) {
    if (BUTTON_EVENTS[i]->_keyCode == keyCode) {
      Event event = BUTTON_EVENTS[i]->_event;
//      Serial.print("Found event index:");
//      Serial.println(i);
//      Serial.print("Corresponds to event: ");
//      Serial.println(int(event));   
      return event;
    }
  }

  return Event::UNKNOWN;
}

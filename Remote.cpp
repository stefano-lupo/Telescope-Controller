#pragma once

#include ".\headers\Remote.h"
#include ".\headers\ButtonCode.h"

const int NUM_ACTIVE_BUTTONS = 12;

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


  // new ButtonEventMapping(ZERO, Event::SET_QUARTER_STEP),
  new ButtonEventMapping(PLUS_100, Event::TOGGLE_BOTTOM_ROW),
  new ButtonEventMapping(PLUS_200, Event::TOGGLE_TOP_ROW),

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

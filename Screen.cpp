#include "Screen.h"

void Screen::setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting");
}

void Screen::update() {
  // lcd.clear();
  clearRows();
  writeCurrent();
  writeTarget();
  writeState();
  // Serial.println(bottomRow);
  // bottomRow[11] = navigator.getEncodedState();
  // bottomRow[12] = navigator.getEncodedState();
  // bottomRow[13] = navigator.getEncodedState();
  // // bottomRow[14] = navigator.getEncodedState();
  // bottomRow[15] = navigator.getEncodedState();
  // Serial.println(navigator.getEncodedState());
  // Serial.println(bottomRow);
  // Serial.println();

  lcd.setCursor(0, 0);
  lcd.print(topRow);
  
  lcd.setCursor(0, 1);
  lcd.print(bottomRow);
}


// void Screen::writeTop(String& str) {
//   sprintf(topRow, str);
// }

// void Screen::writeBottom(String& str) {
//   sprintf(bottomRow, str);
// }

void Screen::writeCurrent() {
  navigator.getCurrentCoord().formatString(topRow);
}

void Screen::writeTarget() {
  navigator.getTargetCoord().formatString(bottomRow);
}

void Screen::writeState() {
  bottomRow[11] = ' ';
  bottomRow[12] = ' ';
  bottomRow[13] = ' ';
  bottomRow[14] = ' ';
  bottomRow[15] = navigator.getEncodedState();
}

void Screen::clearRows() {
  for (int i=0; i<16; i++) {
    bottomRow[i] = ' ';
    topRow[i] = ' ';
  }
}
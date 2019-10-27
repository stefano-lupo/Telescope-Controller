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
  if (bottomRowFlag) {
    writeCameraState();
  } else {
    writeTarget();
  }

  writeState();
  lcd.setCursor(0, 0);
  lcd.print(topRow);
  
  lcd.setCursor(0, 1);
  lcd.print(bottomRow);
}

void Screen::writeCurrent() {
  navigator.getCurrentCoord().formatString(bottomRow);
}

void Screen::writeTarget() {
  navigator.getTargetCoord().formatString(topRow);
}

void Screen::writeCameraState() {
  cameraController.formatString(topRow);
}

void Screen::writeState() {
  bottomRow[11] = ' ';
  bottomRow[12] = ' ';
  bottomRow[13] = ' ';
  bottomRow[14] = ' ';
  bottomRow[15] = navigator.getEncodedNavigationState();
}

void Screen::clearRows() {
  for (int i=0; i<16; i++) {
    bottomRow[i] = ' ';
    topRow[i] = ' ';
  }
}

void Screen::toggleBottomRow() {
  bottomRowFlag = !bottomRowFlag;
}

void Screen::toggleTopRow() {
  topRowFlag = !topRowFlag;
}
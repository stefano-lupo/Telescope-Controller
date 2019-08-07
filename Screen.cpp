#include "Screen.h"

void Screen::setup() {
    this->lcd.init();
    this->lcd.backlight();
    this->lcd.setCursor(0, 1);
    this->lcd.print("Starting Controller");
}

void Screen::write() {
    this->lcd.print("Hello there!");
}
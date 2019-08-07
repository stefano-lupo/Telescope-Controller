#pragma once

#include <LiquidCrystal_I2C.h>
// #include "string.h"

const int I2C_ADDRESS = 0x27;

class Screen {
    public:
        Screen(int sdaPin, int sclPin): sdaPin(sdaPin), sclPin(sclPin), lcd(LiquidCrystal_I2C(I2C_ADDRESS,20, 4)) {};
        void setup();
        void write();

    
    private:
        int sdaPin, sclPin;
        LiquidCrystal_I2C lcd;

};

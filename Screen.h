#pragma once

#include <LiquidCrystal_I2C.h>
#include "Navigator.h"

const int I2C_ADDRESS = 0x27;

class Screen {
    public:
        Screen(const Navigator& navigator): navigator(navigator), lcd(LiquidCrystal_I2C(I2C_ADDRESS, 16, 2)) {};
        void setup();
        void writeTop(String& str);
        void writeBottom(String& str);
        void writeCurrent();
        void writeTarget();
        void writeState();
        void update();
    
    private:
        void clearRows();
        const Navigator& navigator;
        LiquidCrystal_I2C lcd;
        char topRow[16];
        char bottomRow[16];


};

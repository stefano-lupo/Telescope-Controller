#pragma once

#include <LiquidCrystal_I2C.h>
#include "Navigator.h"
#include "CameraController.h"

const int I2C_ADDRESS = 0x27;

class Screen {
    public:
        Screen(const Navigator& navigator, const CameraController& cameraController): navigator(navigator), cameraController(cameraController), lcd(LiquidCrystal_I2C(I2C_ADDRESS, 16, 2)) {};
        void setup();
        void writeTop(String& str);
        void writeBottom(String& str);
        void writeCurrent();
        void writeTarget();
        void writeState();
        void writeCameraState();
        void update();

        void toggleBottomRow();
        void toggleTopRow();
    
    private:
        void clearRows();
        const Navigator& navigator;
        const CameraController& cameraController;
        LiquidCrystal_I2C lcd;
        char topRow[16];
        char bottomRow[16];
        bool bottomRowFlag = false;
        bool topRowFlag = false;


};

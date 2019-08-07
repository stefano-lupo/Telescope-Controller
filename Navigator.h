#pragma once

#include "MotorController.h"
#include "Coordinate.h"

const Coordinate VEGA(18, 37, 36);
const Coordinate ALTAIR(19, 51, 32);
const Coordinate DENEB(20, 42, 7);
const Coordinate ARCTURUS(14, 16, 34);

class Navigator {
    public:
        Navigator(MotorController motorController): motorController(motorController) {};
        void setCurrentCoord(Coordinate coord);
        void setTargetCoord(Coordinate coord);
        void tick();

    
    private:
        unsigned short missedTicks = 0;
        MotorController motorController;
        Coordinate currentCoord();
        Coordinate targetCoord();
};

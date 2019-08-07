#pragma once

#include "NavigatorState.h"
#include "MotorController.h"
#include "Coordinate.h"
#include "Tracker.h"


const int SECONDS_PER_FULL_STEP = 3;
const int NUM_FULL_STEPS_IN_MINUTE = 60 / SECONDS_PER_FULL_STEP;

const Coordinate VEGA(18, 37, 36);
const Coordinate ALTAIR(19, 51, 32);
const Coordinate DENEB(20, 42, 7);
const Coordinate ARCTURUS(14, 16, 34);

class Navigator {
    public:
        Navigator(MotorController motorController, Tracker tracker): motorController(motorController), tracker(tracker) {};
        void setCurrentCoord(Coordinate coord);
        void setTargetCoord(Coordinate coord);
        void tick();
        void moveIfNesc();
        void slewToTarget();
    
    private:
        void slewOneMinute(int deltaValue);
        void slewSeconds(int deltaSecondS);
        boolean getDirectionFromDelta(int deltaValue);

        NavigatorState state = NavigatorState::IDLE;
        unsigned short missedTicks = 0;
        MotorController motorController;
        Tracker tracker;
        Coordinate currentCoord;
        Coordinate targetCoord;
};

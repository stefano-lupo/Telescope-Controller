#pragma once

#include "NavigatorState.h"
#include "MotorController.h"
#include "Coordinate.h"
#include "Tracker.h"


const int SECONDS_PER_FULL_STEP = 3;
const int NUM_FULL_STEPS_IN_MINUTE = 60 / SECONDS_PER_FULL_STEP;
const int NUM_FULL_STEPS_IN_HOUR = 60 * NUM_FULL_STEPS_IN_MINUTE;

const Coordinate VEGA(18, 37, 36);
const Coordinate ALTAIR(19, 51, 32);
const Coordinate DENEB(20, 42, 7);
const Coordinate ARCTURUS(14, 16, 34);

const Coordinate TEST1(0, 0, 0);
const Coordinate TEST2(1, 1, 1);

class Navigator {
    public:
        Navigator(const MotorController& motorController, const Tracker& tracker): motorController(motorController), tracker(tracker) {};
        void setCurrentCoord(const Coordinate&);
        void setTargetCoord(const Coordinate&);
        const Coordinate& getCurrentCoord();
        const Coordinate& getTargetCoord();
        void tick();
        void moveIfNesc();
        void slewToTarget();
        void trackTarget();
        void disableNavigation();
        char getEncodedState();
    
    private:
        const static uint8_t MAX_HOURS_SLEW_PER_TICK = 2;
        void slewHours(int deltaHours);
        void slewMinutes(int deltaMinutes);
        void slewSeconds(int deltaSeconds);
        boolean getDirectionFromDelta(int deltaValue);
        void slew(boolean direction, int numSteps);

        NavigatorState state = NavigatorState::IDLE;
        unsigned short missedTicks = 0;
        const MotorController& motorController;
        const Tracker& tracker;
        Coordinate currentCoord;
        Coordinate targetCoord;
};

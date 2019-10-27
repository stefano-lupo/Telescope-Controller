#pragma once

#include "NavigatorState.h"
#include "MotorController.h"
#include "Coordinate.h"
#include "Tracker.h"


const int SECONDS_PER_FULL_STEP = 3;
const int NUM_FULL_STEPS_IN_MINUTE = 60 / SECONDS_PER_FULL_STEP;
const int NUM_FULL_STEPS_IN_HOUR = 60 * NUM_FULL_STEPS_IN_MINUTE;

const int NUM_HALF_STEPS_IN_HOUR = NUM_FULL_STEPS_IN_HOUR * 2;
const int NUM_HALF_STEPS_IN_MINUTE = NUM_FULL_STEPS_IN_MINUTE * 2;

const Coordinate VEGA(18, 37, 36);
const Coordinate ALTAIR(19, 51, 32);
const Coordinate DENEB(20, 42, 7);
const Coordinate ARCTURUS(14, 16, 34);
const Coordinate NAVI(0, 56, 44);
const Coordinate SHEDAR(0, 40, 32);
const Coordinate DUBHE(11, 4, 52);
const Coordinate ANDROMEDA(0, 43, 50);

class Navigator {
    public:
        Navigator(const MotorController& motorController, const Tracker& tracker): motorController(motorController), tracker(tracker) {};
        void setCurrentCoord(const Coordinate&);
        void setTargetCoord(const Coordinate&);
        const Coordinate& getCurrentCoord();
        const Coordinate& getTargetCoord();
        char getEncodedNavigationState();
        char getEncodedTrackingConfig();
        
        // Actions
        void tick();
        void moveIfNesc();
        void slewToTarget();
        void trackTarget();
        void disableNavigation();
        void setTrackingConfig(int config);
        void nextTrackingConfig();
        void setup();
    
    private:
        const static uint8_t MAX_HOURS_SLEW_PER_TICK = 1;
        const static uint8_t DEFAULT_COOLDOWN_VALUE = 100;
        void slewHours(int deltaHours);
        void slewMinutes(int deltaMinutes);
        void slewSeconds(int deltaSeconds);
        boolean getDirectionFromDelta(int deltaValue);
        void slew(boolean direction, int numSteps);
        void startCooldown();
   

        NavigatorState state = NavigatorState::IDLE;
        unsigned short missedTicks = 0;
        const MotorController& motorController;
        const Tracker& tracker;
        Coordinate currentCoord;
        Coordinate targetCoord;
        uint8_t cooldownCounter = 0;
        bool useFullSteps = true;
        int trackingConfig = 1;
};

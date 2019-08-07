#pragma once

#include <IRremote.h>
#include "Event.h"
#include "ButtonEventMapping.h"
#include "Coordinate.h"

const int DEFAULT_MOTOR_TICK_PERIOD_MS = 750;

class MotorController {
  
    public:
        MotorController(int dirPin, int stepPin, int sleepPin, int resetPin, int ms1, int ms2, int ms3, int ledPin, int interuptPeriodMillis): 
          dirPin(dirPin), stepPin(stepPin), sleepPin(sleepPin), resetPin(resetPin), ms1(ms1), ms2(ms2), ms3(ms3), ledPin(ledPin), interuptPeriodMillis(interuptPeriodMillis) {};
        void setup();
        void toggleMotor();
        void enableMotor();
        void disableMotor();
        void toggleDirection();
        void increaseSpeed();
        void decreaseSpeed();
        void nextStepSize();
        void setStepSize(int stepSizeIndex);
        void stepMotor();
        void stepMotor(int numSteps);
        void tick();
        void moveIfNesc();
    
    private:
        static const int TIME_CHANGE = 5;
        static const int ENCODED_STEP_SIZES[5][3];
        static const int STEP_PULSE_TIME_MICRO = 500;

        int dirPin, stepPin, sleepPin, resetPin, ms1, ms2, ms3, ledPin;
    
        boolean active = true;
        boolean direction = 1;
        int stepSizeIndex = 2;
        int interuptPeriodMillis, accumulatedTimeMillis = 0, motorTickPeriodMillis = DEFAULT_MOTOR_TICK_PERIOD_MS;
        boolean needsMove = false;
};

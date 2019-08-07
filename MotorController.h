#pragma once

#include <IRremote.h>
#include "Event.h"
#include "ButtonEventMapping.h"
#include "Coordinate.h"

const int DEFAULT_MOTOR_TICK_PERIOD_MS = 750;
// const boolean RA = 1;
// const boolean ANTI_RA = 0;

class MotorController {
  
    public:
        MotorController(int dirPin, int stepPin, int sleepPin, int resetPin, int ms1, int ms2, int ms3, int ledPin, int interuptPeriodMillis): 
          dirPin(dirPin), stepPin(stepPin), sleepPin(sleepPin), resetPin(resetPin), ms1(ms1), ms2(ms2), ms3(ms3), ledPin(ledPin), interuptPeriodMillis(interuptPeriodMillis) {};
        
        const static boolean RA = 1;
        const static boolean ANTI_RA = 0;

        void setup();
       
        void enableMotor();
        void disableMotor();

        void toggleDirection();
        void setDirection(boolean direction);

        void increaseSpeed();
        void decreaseSpeed();
        void nextStepSize();
        void setStepSize(int stepSizeIndex);
        void setFullStep();
        void setHalfStep();
        void setQuarterStep();

        void stepMotor();
        void stepMotor(int numSteps);
    
    private:
        static const int TIME_CHANGE = 5;
        static const int ENCODED_STEP_SIZES[5][3];
        static const int STEP_PULSE_TIME_MICRO = 10;

        int dirPin, stepPin, sleepPin, resetPin, ms1, ms2, ms3, ledPin;
    
        boolean active = true;
        boolean direction = RA;
        int stepSizeIndex = 2;
        int interuptPeriodMillis, accumulatedTimeMillis = 0, motorTickPeriodMillis = DEFAULT_MOTOR_TICK_PERIOD_MS;
        boolean needsMove = false;

        void toggleMotor();
};

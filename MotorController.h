#pragma once

#include <IRremote.h>
#include "Event.h"
#include "ButtonEventMapping.h"
#include "Coordinate.h"



class MotorController {
  
    public:
        MotorController(int dirPin, int stepPin, int sleepPin, int ms1, int ms2, int ms3, int interuptPeriodMillis): 
          dirPin(dirPin), stepPin(stepPin), sleepPin(sleepPin), ms1(ms1), ms2(ms2), ms3(ms3), interuptPeriodMillis(interuptPeriodMillis) {};
        
        const static boolean RA = 1;
        const static boolean ANTI_RA = 0;

        void setup();
       
        void enableMotor();
        void disableMotor();

        // void toggleDirection();
        void setDirection(boolean direction);

        void increaseSpeed();
        void decreaseSpeed();
        void nextStepSize();
        void setStepSize(int stepSizeIndex);
        void setFullStep();
        void setHalfStep();
        void setQuarterStep();

        void stepMotor(int numSteps);
    
    private:
        const static int TIME_CHANGE = 5;
        const static int ENCODED_STEP_SIZES[5][3];
        const static int STEP_PULSE_TIME_MICRO = 500;
        const static int DEFAULT_MOTOR_TICK_PERIOD_MS = 750;

        int dirPin, stepPin, sleepPin, ms1, ms2, ms3;
    
        boolean active = false;
        boolean direction = RA;
        int stepSizeIndex = 0;
        int interuptPeriodMillis, accumulatedTimeMillis = 0, motorTickPeriodMillis = DEFAULT_MOTOR_TICK_PERIOD_MS;
        boolean needsMove = false;

        void toggleMotor();
        void stepMotor();
};

#pragma once

#include <IRremote.h>
#include "Event.h"
#include "ButtonEventMapping.h"
#include "Coordinate.h"



class MotorController {
  
    public:
        MotorController(int dirPin, int stepPin, int sleepPin, int ms1, int ms2, int ms3): 
          dirPin(dirPin), stepPin(stepPin), sleepPin(sleepPin), ms1(ms1), ms2(ms2), ms3(ms3) {};
        
        const static boolean RA = 1;
        const static boolean ANTI_RA = 0;

        void setup();
       
        void enableMotor();
        void disableMotor();

        void setDirection(boolean direction);

        void nextStepSize();
        void setStepSize(int stepSizeIndex);
        void setFullStep();
        void setHalfStep();
        void setQuarterStep();

        void stepMotor(int numSteps);
    
    private:
        const static int ENCODED_STEP_SIZES[5][3];
        const static int STEP_PULSE_TIME_MICRO = 500;

        int dirPin, stepPin, sleepPin, ms1, ms2, ms3;
    
        boolean active = false;
        boolean direction = RA;
        int stepSizeIndex = 0;

        void writeMotorState();
        void stepMotor();
};

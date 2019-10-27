#pragma once

#include <inttypes.h>
const int DEFAULT_TRACK_PERIOD = 3000;

class Tracker {
    public:
        Tracker(uint16_t interruptPeriodMillis): interruptPeriodMillis(interruptPeriodMillis) {};
        void tick();
        int getMovesNeeded();
        int getAccumulatedTimeMillis();
        uint16_t getItm();
        void consumeMovesNeeded(int movesNeeded);
        void startTracker();
        void stopTracker();
        int getNumberOfTicks();
        void setMotorTickPeriodMillis(int motorTickPeriodMillis);

    
    private:
        uint16_t interruptPeriodMillis;
        bool started = false;
        int numberOfTicks = 0;
        int motorTickPeriodMillis = DEFAULT_TRACK_PERIOD, movesNeeded = 0, accumulatedTimeMillis = 0;
};

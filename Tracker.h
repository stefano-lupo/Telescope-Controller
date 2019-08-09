#pragma once

#include <inttypes.h>
const int DEFAULT_TRACK_PERIOD = 750;

class Tracker {
    public:
        Tracker(uint16_t interruptPeriodMillis): interruptPeriodMillis(interruptPeriodMillis) {};
        void tick();
        int getMovesNeeded();
        int getAccumulatedTimeMillis();
        uint16_t getItm();
        void consumeMovesNeeded(int movesNeeded);
    private:
        uint16_t interruptPeriodMillis;
        int motorTickPeriodMillis = DEFAULT_TRACK_PERIOD, movesNeeded = 0, accumulatedTimeMillis = 0;
};

#pragma once

const int DEFAULT_TRACK_PERIOD = 750;

class Tracker {
    public:
        Tracker(int interruptPeriodMillis): interruptPeriodMillis(interruptPeriodMillis) {};
        void tick();
        int getMovesNeeded();
        void consumeMovesNeeded(int movesNeeded);
    private:
        int interruptPeriodMillis;
        int motorTickPeriodMillis = DEFAULT_TRACK_PERIOD, movesNeeded = 0, accumulatedTimeMillis = 0;
};

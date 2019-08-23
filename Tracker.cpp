#include "Tracker.h"

void Tracker::startTracker() {
  started = true;
}

void Tracker::stopTracker() {
  started = false;
  accumulatedTimeMillis = 0;
}

void Tracker::tick() {
  if (!started) {
    return;
  }

  accumulatedTimeMillis += interruptPeriodMillis;
  if (accumulatedTimeMillis >= motorTickPeriodMillis) {
    movesNeeded++;
    accumulatedTimeMillis -= motorTickPeriodMillis;
  }
}

int Tracker::getMovesNeeded() {
  return movesNeeded;
}

uint16_t Tracker::getItm() {
  return interruptPeriodMillis;
}

int Tracker::getAccumulatedTimeMillis() {
  return accumulatedTimeMillis;
}

void Tracker::consumeMovesNeeded(int movesNeeded) {
  this->movesNeeded -= movesNeeded;
}
#include "Tracker.h"


void Tracker::tick() {
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
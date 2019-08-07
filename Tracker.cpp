#include "Tracker.h"

void Tracker::tick() {  
  this->accumulatedTimeMillis += this-> interruptPeriodMillis;
  if (this->accumulatedTimeMillis >= this->motorTickPeriodMillis) {
    this->movesNeeded++;
    this->accumulatedTimeMillis -= this->motorTickPeriodMillis;
  }
}

int Tracker::getMovesNeeded() {
  return this->movesNeeded;
}

void Tracker::consumeMovesNeeded(int movesNeeded) {
  this->movesNeeded -= movesNeeded;
}
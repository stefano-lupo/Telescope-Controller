#include ".\headers\Tracker.h"

void Tracker::setMotorTickPeriodMillis(int motorTickPeriodMillis) {
  this->motorTickPeriodMillis = motorTickPeriodMillis;
}

void Tracker::startTracker() {
  started = true;
  numberOfTicks = 0;
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
  this->numberOfTicks += movesNeeded;
}

int Tracker::getNumberOfTicks() {
  return numberOfTicks;
}
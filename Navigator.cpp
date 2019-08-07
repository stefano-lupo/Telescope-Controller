#include "Navigator.h"

void Navigator::moveIfNesc() {
  switch (this->state) {
    case NavigatorState::TRACKING:
      int movesNeeded = this->tracker.getMovesNeeded();
      if (movesNeeded > 0) {
        this->motorController.setDirection(MotorController::RA);
        this->motorController.setQuarterStep();
        this->motorController.stepMotor(movesNeeded);
        this->tracker.consumeMovesNeeded(movesNeeded);
        break;
      }
    case NavigatorState::SLEWING:
      Coordinate delta = this->targetCoord.subtract(this->currentCoord);
      if (delta.hours != 0) {
        this->slewOneMinute(delta.hours);
      } else if (delta.minutes != 0) {
        this->slewOneMinute(delta.minutes);
      } else {
        this->slewSeconds(delta.seconds);
        this->state = NavigatorState::TRACKING;
      }
      break;

    default:
      return;
  }
}

void Navigator::setTargetCoord(Coordinate coord) {
  this->targetCoord = coord;
}

void Navigator::setCurrentCoord(Coordinate coord) {
  this->currentCoord = coord;
}

void Navigator::slewToTarget() {
  this->state = NavigatorState::SLEWING;
}


void Navigator::slewOneMinute(int deltaValue) {
  this->motorController.setDirection(this->getDirectionFromDelta(deltaValue));
  this->motorController.setFullStep();
  this->motorController.stepMotor(NUM_FULL_STEPS_IN_MINUTE);
}

void Navigator::slewSeconds(int deltaSeconds) {
  this->motorController.setDirection(this->getDirectionFromDelta(deltaSeconds));

  int numFullSteps = abs(deltaSeconds) / SECONDS_PER_FULL_STEP;
  this->motorController.setFullStep();
  this->motorController.stepMotor(numFullSteps);

  // Within 3 seconds at this point
  byte remainingSeconds = abs(deltaSeconds) - numFullSteps * SECONDS_PER_FULL_STEP;
  byte numQuarterSteps = remainingSeconds / (SECONDS_PER_FULL_STEP / (4));
  this->motorController.setQuarterStep();
  this->motorController.stepMotor(numQuarterSteps);
}

boolean Navigator::getDirectionFromDelta(int deltaValue) {
  return deltaValue > 0 ? MotorController::RA : MotorController::ANTI_RA;
}
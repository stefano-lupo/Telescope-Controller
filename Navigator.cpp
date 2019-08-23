#include "Navigator.h"

void Navigator::moveIfNesc() {
  switch (state) {
    case NavigatorState::TRACKING: {
      // Serial.println("Tracking");
      int movesNeeded = tracker.getMovesNeeded();
      int accumTime = tracker.getAccumulatedTimeMillis();
      if (movesNeeded > 0) {
        motorController.setDirection(MotorController::RA);
        motorController.setQuarterStep();
        motorController.stepMotor(movesNeeded);
        tracker.consumeMovesNeeded(movesNeeded);
         Serial.print("Tracking: Moved ");
         Serial.println(movesNeeded);
      }

      break;
    }

    case NavigatorState::SLEWING: {
      // Serial.println("Slewing");

      Serial.print("Had target of ");
      char str2[16];
      targetCoord.formatString(str2);
      Serial.println(str2);

      Serial.print("Had current of ");
      char str3[16];
      currentCoord.formatString(str3);
      Serial.println(str3);

      Coordinate delta = Coordinate::getMinimumDelta(currentCoord, targetCoord);
      // Coordinate delta = Coordinate::getMinimumDelta(Coordinate(1, 1, 1), Coordinate(0, 0, 0));
      // Coordinate delta = Coordinate::getMinimumDelta(Coordinate(0, 0, 0), Coordinate(1, 1, 1));
      
      Serial.print("Had delta of ");
      char str[16];
      delta.formatString(str);
      Serial.println(str);

      if (delta.hours != 0) {
        int sign = delta.hours > 0 ? 1 : - 1;
        int hoursToSlewThisTick = min(abs(delta.hours), Navigator::MAX_HOURS_SLEW_PER_TICK) * sign;
        slewHours(hoursToSlewThisTick);
        Serial.print("Slewed ");
        Serial.print(hoursToSlewThisTick);
        Serial.println(" hours");
      } else if (delta.minutes != 0) {
        slewMinutes(delta.minutes);
        Serial.print("Slewed ");
        Serial.print(delta.minutes);
        Serial.println(" minutes");
      } else {
        slewSeconds(delta.seconds);
        Serial.print("Slewed ");
        Serial.print(delta.seconds);
        Serial.println(" seconds");
        trackTarget();
      }


      break;
    }

    case NavigatorState::IDLE: {
      // Serial.println("Idle");
      break;
    }

    default: {
      Serial.println("Navigator in unknown navigation state");
    }
  }
}

void Navigator::setTargetCoord(const Coordinate& coord) {
  targetCoord = coord;
  // char str[16];
  // targetCoord.formatString(str);
  // Serial.print("Setting target: ");
  // Serial.println(str);
}

void Navigator::setCurrentCoord(const Coordinate& coord) {
  currentCoord = coord;
}

const Coordinate& Navigator::getTargetCoord() {
  return targetCoord;
}

const Coordinate& Navigator::getCurrentCoord() {
  return currentCoord;
}

void Navigator::slewToTarget() {
  state = NavigatorState::SLEWING;
  tracker.startTracker();
}

void Navigator::trackTarget() {
  state = NavigatorState::TRACKING;
  // tracker.startTracker();
}

void Navigator::disableNavigation() {
  state = NavigatorState::IDLE;
  tracker.stopTracker();
}

void Navigator::slewHours(int numHours) {
  boolean direction = getDirectionFromDelta(numHours);
  motorController.setFullStep();
  slew(direction, numHours * NUM_FULL_STEPS_IN_HOUR);
  currentCoord.addHours(numHours);
}

void Navigator::slewMinutes(int numMinutes) {
  boolean direction = getDirectionFromDelta(numMinutes);
  motorController.setFullStep();
  slew(direction, numMinutes * NUM_FULL_STEPS_IN_MINUTE);
  currentCoord.addMinutes(numMinutes);
}

void Navigator::slewSeconds(int deltaSeconds) {
  boolean direction = getDirectionFromDelta(deltaSeconds);

  int numFullSteps = abs(deltaSeconds) / SECONDS_PER_FULL_STEP;
  motorController.setFullStep();
  slew(direction, numFullSteps);

  // Within 3 seconds at this point
  byte remainingSeconds = abs(deltaSeconds) - numFullSteps * SECONDS_PER_FULL_STEP;
  byte numQuarterSteps = remainingSeconds / (SECONDS_PER_FULL_STEP / 4);
  motorController.setQuarterStep();
  slew(direction, numQuarterSteps);

  currentCoord.addSeconds(deltaSeconds);
}

void Navigator::slew(boolean direction, int numSteps) {
  motorController.setDirection(direction);
  motorController.stepMotor(abs(numSteps));
}

boolean Navigator::getDirectionFromDelta(int deltaValue) {
  return deltaValue > 0 ? MotorController::RA : MotorController::ANTI_RA;
}


char Navigator::getEncodedState() {
  switch (state) {
    case NavigatorState::IDLE:
      return 'I';
    case NavigatorState::TRACKING:
      return 'T';
    case NavigatorState::SLEWING:
      return 'S';
  }
}

#include "Coordinate.h"


static Coordinate Coordinate::subtract(Coordinate c1, Coordinate c2) {

  return add(c1, negate(c2));

  // int delHours = hours - other.hours;
  // // Serial.println(delHours);

  // int delMins = minutes - other.minutes;
  // // Serial.println(delMins);

  // int delSecs = seconds - other.seconds;
  // // Serial.println(delSecs);

  // return Coordinate(delHours, delMins, delSecs);
}

static Coordinate Coordinate::add(Coordinate c1, Coordinate c2) {
  Coordinate result(c1);
  result.addSeconds(c2.seconds);
  result.addMinutes(c2.minutes);
  result.addHours(c2.hours);
  
  return result;
}


static Coordinate Coordinate::negate(Coordinate c) {
  return Coordinate(-c.hours, -c.minutes, -c.seconds);
}


void Coordinate::addHours(int numHours) {
  hours = addWithWrapping(hours, numHours, 24);
}

void Coordinate::addMinutes(int numMinutes) {
  preAdjustForFlow(minutes, numMinutes, &hours, 60);
  minutes= addWithWrapping(minutes, numMinutes, 60);
}

void Coordinate::addSeconds(int numSeconds) {
  preAdjustForFlow(seconds, numSeconds, &minutes, 60);
  seconds = addWithWrapping(seconds, numSeconds, 60);
}

void Coordinate::formatString(char* str) {
    sprintf(str, "RA %02d:%02d:%02d", hours, minutes, seconds);
}

void Coordinate::preAdjustForFlow(int x1, int x2, int* overflowTarget, int base) {
  if (x1 + x2 >= base) {
    overflowTarget = addWithWrapping(overflowTarget, 1, base);
  } else if (x1 + x2 <= 0) {
    overflowTarget = addWithWrapping(overflowTarget, -1, base);
  }
}

int Coordinate::addWithWrapping(int a, int b, int base) {
  int result = (a+b) % base;
  if (result < 0) {
    return base - result;
  }

  return result;
}


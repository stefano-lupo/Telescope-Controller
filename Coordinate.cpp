#include ".\headers\Coordinate.h"
#include "Arduino.h"

// #include <iostream>


void printit(Coordinate c) {
  // std::cout << c.hours << ":" << c.minutes << ":" << c.seconds << std::endl;
}

Coordinate Coordinate::subtract(Coordinate c1, Coordinate c2) {
  return add(c1, negate(c2));
}

Coordinate Coordinate::add(Coordinate c1, Coordinate c2) {
  Coordinate result(c1);
  
  result.addSeconds(c2.seconds);
  // std::cout << "After Seconds: ";
  // printit(result);

  result.addMinutes(c2.minutes);
  // std::cout << "After minutes: ";
  // printit(result);

  result.addHours(c2.hours);
  
  return result;
}


Coordinate Coordinate::getMinimumDelta(Coordinate current, Coordinate target) {
  Coordinate delta = subtract(target, current);
  // Coordinate delta = signedDelta(target, current);
  // std::cout << "Initial Delta: ";
  // printit(delta);
  // std::cout << std::endl;
  if (abs(delta.hours) > 12) {
    // Add instead of subtract as delta is alr
    delta = negate(subtract(current, target));
    // delta = signedDelta(current, target);
    // delta = subtract(Coordinate(24, 60, 60), target);
    // std::cout << "Revised Delta: ";
    // printit(delta);
    // std::cout << std::endl;
    return delta;
    // return Coordinate(4, 4, 4);
  }

  return delta;
}

Coordinate Coordinate::negate(Coordinate c) {
  // std::cout << "Negating: ";
  // printit(c);
  return Coordinate(-c.hours, -c.minutes, -c.seconds);
}

Coordinate Coordinate::signedDelta(Coordinate c1, Coordinate c2) {
  return Coordinate(c2.hours - c1.hours, c2.minutes - c1.minutes, c2.seconds - c1.seconds);
}

void Coordinate::addHours(int numHours) {
  hours = addWithWrapping(hours, numHours, 24);
}

void Coordinate::addMinutes(int numMinutes) {
  // preAdjustForFlow(minutes, numMinutes, &hours, 60, 24);
  if (minutes + numMinutes >= 60) {
    // *overflowTarget = addWithWrapping(*overflowTarget, 1, overflowBase);
    // std::cout << "Overflowing minutes into hours" << std::endl;
    addHours(1);
  } else if (minutes + numMinutes < 0) {
    // *overflowTarget = addWithWrapping(*overflowTarget, -1, overflowBase);
    // std::cout << "Underflowing minutes into hours" << std::endl;
    addHours(-1);
  }
  minutes = addWithWrapping(minutes, numMinutes, 60);
}

void Coordinate::addSeconds(int numSeconds) {
  // preAdjustForFlow(seconds, numSeconds, &minutes, 60, 60);
  if (seconds + numSeconds >= 60) {
    // std::cout << "Overflowing seconds into minutes" << std::endl;
    // *overflowTarget = addWithWrapping(*overflowTarget, 1, overflowBase);
    addMinutes(1);
  } else if (seconds + numSeconds < 0) {
    // std::cout << "Underflowing seconds into minutes" << std::endl;
    // *overflowTarget = addWithWrapping(*overflowTarget, -1, overflowBase);
    addMinutes(-1);
  }
  seconds = addWithWrapping(seconds, numSeconds, 60);
}

void Coordinate::formatString(char* str) {
    sprintf(str, "RA %02d:%02d:%02d", hours, minutes, seconds);
}

// void Coordinate::preAdjustForFlow(int x1, int x2, int* overflowTarget, int base, int overflowBase) {
//   if (x1 + x2 >= base) {
//     *overflowTarget = addWithWrapping(*overflowTarget, 1, overflowBase);
//   } else if (x1 + x2 <= 0) {
//     *overflowTarget = addWithWrapping(*overflowTarget, -1, overflowBase);
//   }
// }

int Coordinate::addWithWrapping(int a, int b, int base) {
  int result = (a+b) % base;
  if (result < 0) {
    result =  base + result;
    // std::cout << "Result was " << result - base << ", adding " << base << ": " << result << std::endl;
    return result;
  }

  return result;
}


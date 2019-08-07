#include "Coordinate.h"

Coordinate Coordinate::subtract(Coordinate other) {
  return Coordinate(this->hours - other.hours, this->minutes - other.minutes, this->seconds - other.seconds);
}
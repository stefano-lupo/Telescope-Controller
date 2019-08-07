#pragma once

class Coordinate {
    public:
        Coordinate(short hours, short minutes, short seconds): hours(hours), minutes(minutes), seconds(seconds) {};
        Coordinate(): hours(0), minutes(0), seconds(0) {};
        Coordinate subtract(Coordinate other);
        short hours, minutes, seconds;
};

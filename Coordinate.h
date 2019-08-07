#pragma once

class Coordinate {
    public:
        Coordinate(unsigned short hours, unsigned short minutes, unsigned short seconds): hours(hours), minutes(minutes), seconds(seconds) {};
        Coordinate(): hours(0), minutes(0), seconds(0) {};
    private:
        unsigned short hours, minutes, seconds;
};

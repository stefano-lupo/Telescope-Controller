#pragma once

#include <stdio.h>

class Coordinate {
    public:
        Coordinate(int hours, int minutes, int seconds): hours(hours), minutes(minutes), seconds(seconds) {};
        Coordinate(): hours(-1), minutes(-1), seconds(-1) {};
        Coordinate(const Coordinate& c): hours(c.hours), minutes(c.minutes), seconds(c.seconds) {};
        static Coordinate add(Coordinate, Coordinate);
        static Coordinate subtract(Coordinate, Coordinate);
        static Coordinate negate(Coordinate);
        // static Coordinate getMinDistanceBetween(Coordinate);
        void addHours(int numHours);
        void addMinutes(int numMinutes);
        void addSeconds(int numSeconds);
        void formatString(char* str);
        int hours, minutes, seconds;

    private:
        void preAdjustForFlow(int x1, int x2, int* overflowTarget, int base);
        int addWithWrapping(int a, int b, int base);
};

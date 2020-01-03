#pragma once

#include "multiCameraIrControl.h"

const long DEFAULT_SHUTTER_TIME_MILLIS = 45000;
const int SHUTTER_TIME_CHANGE_RESOLUTION_MILLIS = 50000;

class CameraController {
    public:
        CameraController(int irPin, int interuptPeriodMillis): irPin(irPin), interuptPeriodMillis(interuptPeriodMillis), camera(irPin) {};
        void setup();
        void enableCapturing();
        void disableCapturing();
        void toggleShutter();
        void increaseShutterTime();
        void decreaseShutterTime();
        void snapShot();
        void setShutterTime(int shutterTimeMillis);
        void shutterIfNesc();
        void tick();
        void formatString(char* str);
    
    private:
        int irPin, interuptPeriodMillis;
        long shutterTimeMillis = DEFAULT_SHUTTER_TIME_MILLIS, 
            accumulatedTimeMillis = 0,
            cooldownPeriodMillis = 15000;
        boolean hasShutterToggle = false;
        boolean active = false;
        Sony camera;
};

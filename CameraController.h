#pragma once

#include "multiCameraIrControl.h"

const int DEFAULT_SHUTTER_TIME_MILLIS = 15000;
const int SHUTTER_TIME_CHANGE_RESOLUTION_MILLIS = 500;

class CameraController {
    public:
        CameraController(int irPin, int interuptPeriodMillis): irPin(irPin), interuptPeriodMillis(interuptPeriodMillis), camera(irPin), shutterTimeMillis(DEFAULT_SHUTTER_TIME_MILLIS) {};
        void setup();
        void enableCapturing();
        void disableCapturing();
        void toggleShutter();
        void increaseShutterTime();
        void decreaseShutterTime();
        void setShutterTime(int shutterTimeMillis);
        void shutterIfNesc();
        void tick();
    
    private:
        int irPin, interuptPeriodMillis, shutterTimeMillis, accumulatedTimeMillis = 0;
        boolean hasShutterToggle = false;
        boolean active = false;
        Sony camera;
};

#pragma once

#include <IRremote.h>
#include "Event.h"
#include "ButtonEventMapping.h"

class Remote {
    public:
        Remote(int pin): pin(pin), irReceiver(pin) {};
        void setup();
        Event checkForPress();
    
    private:
        int pin;
        IRrecv irReceiver;
        decode_results &decodedSignal;
        Event decodeKeyPress(unsigned long keyCode);
};

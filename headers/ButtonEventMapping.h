#pragma once

#include "Event.h"

class ButtonEventMapping {
    public:
        ButtonEventMapping(unsigned long keyCode, Event event): keyCode(keyCode), event(event) {};
        unsigned long keyCode;
        Event event;
};

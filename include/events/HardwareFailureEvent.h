#ifndef HARDWARE_FAILURE_EVENT_H
#define HARDWARE_FAILURE_EVENT_H

#include "Event.h"

class HardwareFailureEvent : public Event {
public:
    HardwareFailureEvent(const std::string& message)
        : Event("HardwareFailureEvent", message) {}
};

#endif
#ifndef EMERGENCY_MODE_ACTIVATED_H
#define EMERGENCY_MODE_ACTIVATED_H

#include "Event.h"

class EmergencyModeActivated : public Event {
public:
    EmergencyModeActivated(const std::string& message)
        : Event("EmergencyModeActivated", message) {}
};

#endif
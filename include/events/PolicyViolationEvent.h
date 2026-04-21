#ifndef POLICY_VIOLATION_EVENT_H
#define POLICY_VIOLATION_EVENT_H

#include "Event.h"

class PolicyViolationEvent : public Event {
public:
    PolicyViolationEvent(const std::string& message)
        : Event("PolicyViolationEvent", message) {}
};

#endif
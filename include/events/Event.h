#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
protected:
    std::string eventName;

public:
    Event(const std::string& eventName) : eventName(eventName) {}
    virtual ~Event() = default;
    std::string getEventName() const { return eventName; }
};

#endif
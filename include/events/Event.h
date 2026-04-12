#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
protected:
    std::string eventName;
    std::string message;

public:
    Event(const std::string& eventName, const std::string& message = "")
        : eventName(eventName), message(message) {}

    virtual ~Event() = default;

    std::string getEventName() const { return eventName; }
    std::string getMessage() const { return message; }
};

#endif
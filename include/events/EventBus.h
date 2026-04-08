#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <vector>
#include "EventListener.h"

class EventBus {
private:
    std::vector<EventListener*> listeners;

public:
    void subscribe(EventListener* listener);
    void publish(const Event& event);
};

#endif
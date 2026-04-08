#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "Event.h"

class EventListener {
public:
    virtual void update(const Event& event) = 0;
    virtual ~EventListener() = default;
};

#endif
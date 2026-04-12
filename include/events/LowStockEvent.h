#ifndef LOW_STOCK_EVENT_H
#define LOW_STOCK_EVENT_H

#include "Event.h"

class LowStockEvent : public Event {
public:
    LowStockEvent(const std::string& message)
        : Event("LowStockEvent", message) {}
};

#endif
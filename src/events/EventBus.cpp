#include "../../include/events/EventBus.h"

void EventBus::subscribe(EventListener* listener) {
    listeners.push_back(listener);
}

void EventBus::publish(const Event& event) {
    for (EventListener* listener : listeners) {
        listener->update(event);
    }
}
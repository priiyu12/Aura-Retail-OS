#include "../../include/monitoring/CityMonitoringSystem.h"

void CityMonitoringSystem::update(const Event& event) {
    std::cout << "[CITY MONITORING] " << event.getEventName();

    if (!event.getMessage().empty()) {
        std::cout << " -> " << event.getMessage();
    }

    if (event.getEventName() == "LowStockEvent") {
        std::cout << " [Action: refill planning suggested]";
    }
    else if (event.getEventName() == "HardwareFailureEvent") {
        std::cout << " [Action: maintenance unit should inspect kiosk]";
    }
    else if (event.getEventName() == "PolicyViolationEvent") {
        std::cout << " [Action: rule enforcement triggered]";
    }

    std::cout << "\n";
}
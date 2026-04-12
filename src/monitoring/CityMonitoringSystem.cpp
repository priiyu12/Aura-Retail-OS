#include "../../include/monitoring/CityMonitoringSystem.h"

void CityMonitoringSystem::update(const Event& event) {
    std::cout << "[CITY MONITORING] " << event.getEventName();

    if (!event.getMessage().empty()) {
        std::cout << " -> " << event.getMessage();
    }

    std::cout << "\n";
}
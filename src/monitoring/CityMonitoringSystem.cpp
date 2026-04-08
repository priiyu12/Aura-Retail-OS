#include "../../include/monitoring/CityMonitoringSystem.h"

void CityMonitoringSystem::update(const Event& event) {
    std::cout << "[MONITORING] Alert received: " << event.getEventName() << "\n";
}
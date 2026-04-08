#ifndef CITY_MONITORING_SYSTEM_H
#define CITY_MONITORING_SYSTEM_H

#include "../events/EventListener.h"
#include <iostream>

class CityMonitoringSystem : public EventListener {
public:
    void update(const Event& event) override;
};

#endif
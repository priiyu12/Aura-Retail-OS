#include "../../include/core/CentralRegistry.h"

CentralRegistry::CentralRegistry()
    : activeKioskType(""), currentMode("ACTIVE") {}

CentralRegistry& CentralRegistry::getInstance() {
    static CentralRegistry instance;
    return instance;
}

void CentralRegistry::setActiveKioskType(const std::string& kioskType) {
    activeKioskType = kioskType;
}

std::string CentralRegistry::getActiveKioskType() const {
    return activeKioskType;
}

void CentralRegistry::setCurrentMode(const std::string& mode) {
    currentMode = mode;
}

std::string CentralRegistry::getCurrentMode() const {
    return currentMode;
}
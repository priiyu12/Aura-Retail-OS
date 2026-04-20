#ifndef CENTRAL_REGISTRY_H
#define CENTRAL_REGISTRY_H

#include <string>

class CentralRegistry {
private:
    std::string activeKioskType;
    std::string currentMode;

    CentralRegistry();
    CentralRegistry(const CentralRegistry&) = delete;
    CentralRegistry& operator=(const CentralRegistry&) = delete;

public:
    static CentralRegistry& getInstance();

    void setActiveKioskType(const std::string& kioskType);
    std::string getActiveKioskType() const;

    void setCurrentMode(const std::string& mode);
    std::string getCurrentMode() const;
};

#endif
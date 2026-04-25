#include "../../include/persistence/ConfigStorage.h"
#include <fstream>
#include <iostream>

bool ConfigStorage::saveConfig(const std::string& kioskType,
                               const std::string& mode,
                               const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "[PERSISTENCE] Failed to open config file for writing.\n";
        return false;
    }

    file << "kioskType=" << kioskType << "\n";
    file << "mode=" << mode << "\n";

    file.close();
    std::cout << "[PERSISTENCE] Config saved to " << filename << "\n";
    return true;
}
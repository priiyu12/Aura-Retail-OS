#ifndef CONFIG_STORAGE_H
#define CONFIG_STORAGE_H

#include <string>

class ConfigStorage {
public:
    bool saveConfig(const std::string& kioskType,
                    const std::string& mode,
                    const std::string& filename) const;
};

#endif
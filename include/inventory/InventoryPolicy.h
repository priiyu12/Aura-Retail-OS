#ifndef INVENTORY_POLICY_H
#define INVENTORY_POLICY_H

#include <string>
#include "../models/Product.h"

class InventoryPolicy {
public:
    bool validatePurchase(const std::string& kioskType,
                          const Product& product,
                          int quantity,
                          const std::string& currentMode,
                          std::string& reason) const;

    bool validateRestock(const std::string& kioskType,
                         int quantity,
                         std::string& reason) const;

    std::string getEnvironmentNote(const std::string& kioskType) const;
};

#endif
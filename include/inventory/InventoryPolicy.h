#ifndef INVENTORY_POLICY_H
#define INVENTORY_POLICY_H

#include <string>
#include "../models/Product.h"

class InventoryPolicy {
public:
    bool validatePurchase(const std::string& kioskType,
                          const Product& product,
                          int quantity,
                          std::string& reason) const;

    bool validateRestock(int quantity, std::string& reason) const;
};

#endif
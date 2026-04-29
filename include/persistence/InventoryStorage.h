#ifndef INVENTORY_STORAGE_H
#define INVENTORY_STORAGE_H

#include <string>
#include "../inventory/InventorySystem.h"

class InventoryStorage {
public:
    bool saveInventory(const InventorySystem& inventory, const std::string& filename) const;
};

#endif
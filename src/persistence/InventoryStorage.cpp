#include "../../include/persistence/InventoryStorage.h"
#include "../../include/models/Product.h"
#include <fstream>
#include <iostream>
#include <vector>

bool InventoryStorage::saveInventory(const InventorySystem& inventory, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "[PERSISTENCE] Failed to open inventory file for writing.\n";
        return false;
    }

    file << "productId,name,category,basePrice,stock,reservedStock,faultyStock,lowStockThreshold,restricted,essential\n";

    const std::map<int, Product>& products = inventory.getAllProducts();

    for (const auto& pair : products) {
        const Product& product = pair.second;
        file << product.getProductId() << ","
            << product.getName() << ","
            << product.getCategory() << ","
            << product.getBasePrice() << ","
            << product.getStock() << ","
            << product.getReservedStock() << ","
            << product.getFaultyStock() << ","
            << product.getLowStockThreshold() << ","
            << product.isRestricted() << ","
            << product.isEssential() << "\n";
    }

    file.close();
    std::cout << "[PERSISTENCE] Inventory saved to " << filename << "\n";
    return true;
}
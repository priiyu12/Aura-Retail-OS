#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <map>
#include "../models/Product.h"

class InventorySystem {
private:
    std::map<int, Product> products;

public:
    void addProduct(const Product& product);
    bool checkAvailability(int productId, int quantity);
    bool reserveItem(int productId, int quantity);
    void releaseItem(int productId, int quantity);
    bool confirmPurchase(int productId, int quantity);
    void restockItem(int productId, int quantity);
    Product* getProduct(int productId);
    void showInventory() const;
    bool isLowStock(int productId) const;
};

#endif
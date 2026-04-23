#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <map>
#include "Bundle.h"
#include "../models/Product.h"

class InventorySystem {
private:
    std::map<int, Product> products;
    std::map<int, Bundle> bundles;

public:
    void addProduct(const Product& product);
    void addBundle(const Bundle& bundle);

    bool checkAvailability(int productId, int quantity);
    bool reserveItem(int productId, int quantity);
    void releaseItem(int productId, int quantity);
    bool confirmPurchase(int productId, int quantity);
    void restockItem(int productId, int quantity);

    Product* getProduct(int productId);
    Bundle* getBundle(int bundleId);

    bool checkBundleAvailability(int bundleId);
    bool reserveBundle(int bundleId);
    void releaseBundle(int bundleId);
    bool confirmBundlePurchase(int bundleId);

    double calculateBundleBasePrice(int bundleId) const;

    void showInventory() const;
    void showBundles() const;
    bool isLowStock(int productId) const;
    const std::map<int, Product>& getAllProducts() const;
};

#endif
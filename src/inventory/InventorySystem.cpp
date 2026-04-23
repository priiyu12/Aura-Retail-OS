#include "../../include/inventory/InventorySystem.h"
#include <iostream>

void InventorySystem::addProduct(const Product& product) {
    products[product.getProductId()] = product;
}

void InventorySystem::addBundle(const Bundle& bundle) {
    bundles[bundle.getBundleId()] = bundle;
}

bool InventorySystem::checkAvailability(int productId, int quantity) {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    return it->second.getAvailableStock() >= quantity;
}

bool InventorySystem::reserveItem(int productId, int quantity) {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    return it->second.reserveStock(quantity);
}

void InventorySystem::releaseItem(int productId, int quantity) {
    auto it = products.find(productId);
    if (it != products.end()) {
        it->second.releaseReservedStock(quantity);
    }
}

bool InventorySystem::confirmPurchase(int productId, int quantity) {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    return it->second.confirmPurchase(quantity);
}

void InventorySystem::restockItem(int productId, int quantity) {
    auto it = products.find(productId);
    if (it != products.end()) {
        it->second.restock(quantity);
    }
}

Product* InventorySystem::getProduct(int productId) {
    auto it = products.find(productId);
    if (it == products.end()) return nullptr;
    return &(it->second);
}

Bundle* InventorySystem::getBundle(int bundleId) {
    auto it = bundles.find(bundleId);
    if (it == bundles.end()) return nullptr;
    return &(it->second);
}

bool InventorySystem::checkBundleAvailability(int bundleId) {
    auto it = bundles.find(bundleId);
    if (it == bundles.end()) return false;

    const Bundle& bundle = it->second;
    std::vector<int> productIds = bundle.getProductIds();
    std::vector<int> quantities = bundle.getQuantities();

    for (size_t i = 0; i < productIds.size(); ++i) {
        if (!checkAvailability(productIds[i], quantities[i])) {
            return false;
        }
    }
    return true;
}

bool InventorySystem::reserveBundle(int bundleId) {
    auto it = bundles.find(bundleId);
    if (it == bundles.end()) return false;

    const Bundle& bundle = it->second;
    std::vector<int> productIds = bundle.getProductIds();
    std::vector<int> quantities = bundle.getQuantities();

    if (!checkBundleAvailability(bundleId)) return false;

    for (size_t i = 0; i < productIds.size(); ++i) {
        reserveItem(productIds[i], quantities[i]);
    }
    return true;
}

void InventorySystem::releaseBundle(int bundleId) {
    auto it = bundles.find(bundleId);
    if (it == bundles.end()) return;

    const Bundle& bundle = it->second;
    std::vector<int> productIds = bundle.getProductIds();
    std::vector<int> quantities = bundle.getQuantities();

    for (size_t i = 0; i < productIds.size(); ++i) {
        releaseItem(productIds[i], quantities[i]);
    }
}

bool InventorySystem::confirmBundlePurchase(int bundleId) {
    auto it = bundles.find(bundleId);
    if (it == bundles.end()) return false;

    const Bundle& bundle = it->second;
    std::vector<int> productIds = bundle.getProductIds();
    std::vector<int> quantities = bundle.getQuantities();

    for (size_t i = 0; i < productIds.size(); ++i) {
        if (!confirmPurchase(productIds[i], quantities[i])) {
            return false;
        }
    }
    return true;
}

double InventorySystem::calculateBundleBasePrice(int bundleId) const {
    auto it = bundles.find(bundleId);
    if (it == bundles.end()) return 0.0;

    const Bundle& bundle = it->second;
    std::vector<int> productIds = bundle.getProductIds();
    std::vector<int> quantities = bundle.getQuantities();

    double total = 0.0;
    for (size_t i = 0; i < productIds.size(); ++i) {
        auto pit = products.find(productIds[i]);
        if (pit != products.end()) {
            total += pit->second.getBasePrice() * quantities[i];
        }
    }
    return total;
}

void InventorySystem::showInventory() const {
    std::cout << "\nAvailable Products:\n";
    for (const auto& pair : products) {
        const Product& p = pair.second;
        std::cout << "Product ID: " << p.getProductId()
                  << " | Name: " << p.getName()
                  << " | Category: " << p.getCategory()
                  << " | Price: " << p.getBasePrice()
                  << " | Available Stock: " << p.getAvailableStock()
                  << "\n";
    }
}

void InventorySystem::showBundles() const {
    std::cout << "\nAvailable Bundles:\n";
    if (bundles.empty()) {
        std::cout << "No bundles available.\n";
        return;
    }

    for (const auto& pair : bundles) {
        const Bundle& b = pair.second;
        std::cout << "Bundle ID: " << b.getBundleId()
                  << " | Name: " << b.getName()
                  << " | Base Price Total: " << calculateBundleBasePrice(b.getBundleId())
                  << "\n";
    }
}

bool InventorySystem::isLowStock(int productId) const {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    return it->second.getAvailableStock() <= it->second.getLowStockThreshold();
}
const std::map<int, Product>& InventorySystem::getAllProducts() const {
    return products;
}
#include "../../include/inventory/InventorySystem.h"
#include <iostream>

void InventorySystem::addProduct(const Product& product) {
    products[product.getProductId()] = product;
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

void InventorySystem::showInventory() const {
    std::cout << "\nAvailable Products:\n";
    for (const auto& pair : products) {
        const Product& p = pair.second;
        std::cout << "Product ID: " << p.getProductId()
                  << " | Name: " << p.getName()
                  << " | Price: " << p.getBasePrice()
                  << " | Available Stock: " << p.getAvailableStock()
                  << "\n";
    }
}

bool InventorySystem::isLowStock(int productId) const {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    return it->second.getAvailableStock() <= it->second.getLowStockThreshold();
}
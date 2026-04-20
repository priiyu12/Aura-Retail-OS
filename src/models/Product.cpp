#include "../../include/models/Product.h"
#include <algorithm>

Product::Product()
    : productId(0),
      name(""),
      category(""),
      basePrice(0.0),
      stock(0),
      reservedStock(0),
      faultyStock(0),
      lowStockThreshold(2),
      restricted(false),
      essential(false) {}

Product::Product(int productId,
                 const std::string& name,
                 const std::string& category,
                 double basePrice,
                 int stock,
                 int lowStockThreshold,
                 bool restricted,
                 bool essential)
    : productId(productId),
      name(name),
      category(category),
      basePrice(basePrice),
      stock(stock),
      reservedStock(0),
      faultyStock(0),
      lowStockThreshold(lowStockThreshold),
      restricted(restricted),
      essential(essential) {}

int Product::getProductId() const { return productId; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getBasePrice() const { return basePrice; }
int Product::getStock() const { return stock; }
int Product::getReservedStock() const { return reservedStock; }
int Product::getFaultyStock() const { return faultyStock; }
int Product::getLowStockThreshold() const { return lowStockThreshold; }
bool Product::isRestricted() const { return restricted; }
bool Product::isEssential() const { return essential; }

int Product::getAvailableStock() const {
    return stock - reservedStock - faultyStock;
}

bool Product::reserveStock(int quantity) {
    if (quantity <= 0) return false;
    if (getAvailableStock() < quantity) return false;
    reservedStock += quantity;
    return true;
}

void Product::releaseReservedStock(int quantity) {
    reservedStock = std::max(0, reservedStock - quantity);
}

bool Product::confirmPurchase(int quantity) {
    if (quantity <= 0) return false;
    if (reservedStock < quantity) return false;

    reservedStock -= quantity;
    stock -= quantity;
    return true;
}

void Product::restock(int quantity) {
    if (quantity > 0) {
        stock += quantity;
    }
}
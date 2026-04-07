#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productId;
    std::string name;
    double basePrice;
    int stock;
    int reservedStock;
    int faultyStock;
    int lowStockThreshold;

public:
    Product();
    Product(int productId, const std::string& name, double basePrice, int stock, int lowStockThreshold = 2);

    int getProductId() const;
    std::string getName() const;
    double getBasePrice() const;
    int getStock() const;
    int getReservedStock() const;
    int getFaultyStock() const;
    int getLowStockThreshold() const;

    int getAvailableStock() const;

    bool reserveStock(int quantity);
    void releaseReservedStock(int quantity);
    bool confirmPurchase(int quantity);
    void restock(int quantity);
};

#endif
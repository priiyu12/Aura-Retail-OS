#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productId;
    std::string name;
    std::string category;
    double basePrice;
    int stock;
    int reservedStock;
    int faultyStock;
    int lowStockThreshold;
    bool restricted;
    bool essential;

public:
    Product();
    Product(int productId,
            const std::string& name,
            const std::string& category,
            double basePrice,
            int stock,
            int lowStockThreshold = 2,
            bool restricted = false,
            bool essential = false);

    int getProductId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getBasePrice() const;
    int getStock() const;
    int getReservedStock() const;
    int getFaultyStock() const;
    int getLowStockThreshold() const;
    bool isRestricted() const;
    bool isEssential() const;

    int getAvailableStock() const;

    bool reserveStock(int quantity);
    void releaseReservedStock(int quantity);
    bool confirmPurchase(int quantity);
    void restock(int quantity);
};

#endif
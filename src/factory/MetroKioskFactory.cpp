#include "../../include/factory/MetroKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/StandardPricing.h"

void MetroKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(201, "Water Bottle", 20.0, 15, 3));
    inventory.addProduct(Product(202, "Snack Pack", 35.0, 10, 2));
    inventory.addProduct(Product(203, "Umbrella", 150.0, 4, 1));
}

PricingStrategy* MetroKioskFactory::createPricingStrategy() {
    return new StandardPricing();
}

std::string MetroKioskFactory::getKioskType() const {
    return "Metro";
}
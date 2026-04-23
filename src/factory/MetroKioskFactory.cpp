#include "../../include/factory/MetroKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/StandardPricing.h"

void MetroKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(201, "Water Bottle", "Beverage", 20.0, 15, 3, false, true));
    inventory.addProduct(Product(202, "Snack Pack", "Food", 35.0, 10, 2, false, true));
    inventory.addProduct(Product(203, "Umbrella", "Travel", 150.0, 4, 1, false, false));
    inventory.addBundle(Bundle(
    901,
    "Travel Combo",
    {201, 202},
    {1, 1}
));
}

PricingStrategy* MetroKioskFactory::createPricingStrategy() {
    return new StandardPricing();
}

std::string MetroKioskFactory::getKioskType() const {
    return "Metro";
}
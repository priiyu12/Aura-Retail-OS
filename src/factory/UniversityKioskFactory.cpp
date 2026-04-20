#include "../../include/factory/UniversityKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/DiscountPricing.h"

void UniversityKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(301, "Earphones", 500.0, 6, 1));
    inventory.addProduct(Product(302, "Notebook", 40.0, 12, 2));
    inventory.addProduct(Product(303, "Charger", 700.0, 5, 1));
}

PricingStrategy* UniversityKioskFactory::createPricingStrategy() {
    return new DiscountPricing();
}

std::string UniversityKioskFactory::getKioskType() const {
    return "University";
}
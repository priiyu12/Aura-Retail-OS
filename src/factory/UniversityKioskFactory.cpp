#include "../../include/factory/UniversityKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/DiscountPricing.h"

void UniversityKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(301, "Earphones", "Electronics", 500.0, 6, 1, false, false));
    inventory.addProduct(Product(302, "Notebook", "Stationery", 40.0, 12, 2, false, true));
    inventory.addProduct(Product(303, "Charger", "Electronics", 700.0, 5, 1, false, false));
    inventory.addBundle(Bundle(
    902,
    "Study Essentials Pack",
    {302, 303},
    {2, 1}
));
}

PricingStrategy* UniversityKioskFactory::createPricingStrategy() {
    return new DiscountPricing();
}

std::string UniversityKioskFactory::getKioskType() const {
    return "University";
}
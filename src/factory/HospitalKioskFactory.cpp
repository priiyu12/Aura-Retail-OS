#include "../../include/factory/HospitalKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/StandardPricing.h"

void HospitalKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(101, "Paracetamol", "Medicine", 20.0, 10, 2, false, true));
    inventory.addProduct(Product(102, "Prescription Medicine", "Medicine", 120.0, 5, 1, true, true));
    inventory.addProduct(Product(103, "Sanitizer", "Hygiene", 50.0, 8, 2, false, true));
    inventory.addBundle(Bundle(
    904,
    "Basic Care Pack",
    {101, 103},
    {1, 1}
));
}

PricingStrategy* HospitalKioskFactory::createPricingStrategy() {
    return new StandardPricing();
}

std::string HospitalKioskFactory::getKioskType() const {
    return "Hospital";
}
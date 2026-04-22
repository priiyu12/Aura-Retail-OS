#include "../../include/factory/HospitalKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/StandardPricing.h"

void HospitalKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(101, "Paracetamol", 20.0, 10, 2));
    inventory.addProduct(Product(102, "Prescription Medicine", 120.0, 5, 1));
    inventory.addProduct(Product(103, "Sanitizer", 50.0, 8, 2));
}

PricingStrategy* HospitalKioskFactory::createPricingStrategy() {
    return new StandardPricing();
}
#include "../../include/factory/HospitalKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/StandardPricing.h"

void HospitalKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(101, "Paracetamol", "Medicine", 20.0, 10, 2, false, true));
    inventory.addProduct(Product(102, "Prescription Medicine", "Medicine", 120.0, 5, 1, true, true));
    inventory.addProduct(Product(103, "Sanitizer", "Hygiene", 50.0, 8, 2, false, true));
}

PricingStrategy* HospitalKioskFactory::createPricingStrategy() {
    return new StandardPricing();
}

std::string HospitalKioskFactory::getKioskType() const {
    return "Hospital";
}
std::string HospitalKioskFactory::getKioskType() const {
    return "Hospital";
}
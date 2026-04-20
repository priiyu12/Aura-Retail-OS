#include "../../include/factory/DisasterReliefKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/EmergencyPricing.h"

void DisasterReliefKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Product(401, "Emergency Kit", 250.0, 6, 2));
    inventory.addProduct(Product(402, "Water Pack", 80.0, 10, 2));
    inventory.addProduct(Product(403, "First Aid Box", 180.0, 5, 1));
}

PricingStrategy* DisasterReliefKioskFactory::createPricingStrategy() {
    return new EmergencyPricing();
}

std::string DisasterReliefKioskFactory::getKioskType() const {
    return "Disaster Relief";
}
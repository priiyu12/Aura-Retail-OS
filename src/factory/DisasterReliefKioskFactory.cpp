#include "../../include/factory/DisasterReliefKioskFactory.h"
#include "../../include/models/Product.h"
#include "../../include/pricing/EmergencyPricing.h"

void DisasterReliefKioskFactory::setupInventory(InventorySystem& inventory) {
    inventory.addProduct(Produgit push origin mainct(401, "Emergency Kit", "Relief", 250.0, 6, 2, false, true));
    inventory.addProduct(Product(402, "Water Pack", "Relief", 80.0, 10, 2, false, true));
    inventory.addProduct(Product(403, "First Aid Box", "Relief", 180.0, 5, 1, false, true));
}

PricingStrategy* DisasterReliefKioskFactory::createPricingStrategy() {
    return new EmergencyPricing();
}

std::string DisasterReliefKioskFactory::getKioskType() const {
    return "Disaster Relief";
}
#include "../../include/inventory/InventoryPolicy.h"

bool InventoryPolicy::validatePurchase(const std::string& kioskType,
                                       const Product& product,
                                       int quantity,
                                       std::string& reason) const {
    if (quantity <= 0) {
        reason = "Quantity must be greater than zero.";
        return false;
    }

    if (kioskType == "Hospital" && product.getName() == "Prescription Medicine" && quantity > 2) {
        reason = "Hospital kiosk allows maximum 2 units of Prescription Medicine per transaction.";
        return false;
    }

    if (kioskType == "Disaster Relief" && quantity > 2) {
        reason = "Disaster Relief kiosk allows maximum 2 essential items per transaction.";
        return false;
    }

    reason = "";
    return true;
}

bool InventoryPolicy::validateRestock(int quantity, std::string& reason) const {
    if (quantity <= 0) {
        reason = "Restock quantity must be greater than zero.";
        return false;
    }

    reason = "";
    return true;
}
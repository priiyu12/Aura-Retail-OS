#include "../../include/inventory/InventoryPolicy.h"

bool InventoryPolicy::validatePurchase(const std::string& kioskType,
                                       const Product& product,
                                       int quantity,
                                       const std::string& currentMode,
                                       std::string& reason) const {
    if (quantity <= 0) {
        reason = "Quantity must be greater than zero.";
        return false;
    }

    // State-sensitive policy note
    if (currentMode == "EMERGENCY_LOCKDOWN" && kioskType != "Disaster Relief") {
        reason = "Only critical operations are expected during emergency lockdown.";
        return false;
    }

    // Hospital-specific rules
    if (kioskType == "Hospital") {
        if (product.isRestricted() && quantity > 2) {
            reason = "Hospital kiosk allows maximum 2 units for restricted prescription items.";
            return false;
        }
    }

    // Metro-specific rules
    if (kioskType == "Metro") {
        if (quantity > 5) {
            reason = "Metro kiosk allows a maximum of 5 units per purchase for quick-service flow.";
            return false;
        }
    }

    // University-specific rules
    if (kioskType == "University") {
        if (product.getCategory() == "Electronics" && quantity > 2) {
            reason = "University kiosk allows a maximum of 2 electronics items per transaction.";
            return false;
        }
    }

    // Disaster relief-specific rules
    if (kioskType == "Disaster Relief") {
        if (!product.isEssential()) {
            reason = "Disaster Relief kiosk only allows essential items.";
            return false;
        }
        if (quantity > 2) {
            reason = "Disaster Relief kiosk allows maximum 2 essential items per transaction.";
            return false;
        }
    }

    reason = "";
    return true;
}

bool InventoryPolicy::validateRestock(const std::string& kioskType,
                                      int quantity,
                                      std::string& reason) const {
    if (quantity <= 0) {
        reason = "Restock quantity must be greater than zero.";
        return false;
    }

    if (kioskType == "Metro" && quantity > 50) {
        reason = "Metro kiosk restock quantity is too high for one admin action.";
        return false;
    }

    reason = "";
    return true;
}

std::string InventoryPolicy::getEnvironmentNote(const std::string& kioskType) const {
    if (kioskType == "Hospital") {
        return "Hospital kiosk handles medical essentials and restricted prescription items.";
    }
    if (kioskType == "Metro") {
        return "Metro kiosk supports quick daily-use purchases with lightweight policy limits.";
    }
    if (kioskType == "University") {
        return "University kiosk supports electronics and stationery with student-friendly behavior.";
    }
    if (kioskType == "Disaster Relief") {
        return "Disaster Relief kiosk prioritizes essential items with strict emergency purchase limits.";
    }
    return "Generic kiosk environment.";
}
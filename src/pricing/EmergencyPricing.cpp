#include "../../include/pricing/EmergencyPricing.h"
<<<<<<< HEAD

double EmergencyPricing::calculatePrice(double basePrice, int quantity) {
    return (basePrice * quantity) * 0.80;
=======
#include <sstream>

double EmergencyPricing::calculatePrice(double basePrice, int quantity) {
    return (basePrice * quantity) * 0.80;
}

std::string EmergencyPricing::getStrategyName() const {
    return "EmergencyPricing";
}

std::string EmergencyPricing::getPricingExplanation(double basePrice, int quantity) const {
    double baseTotal = basePrice * quantity;
    double finalTotal = baseTotal * 0.80;

    std::ostringstream out;
    out << "[PRICING] Strategy Applied: EmergencyPricing\n";
    out << "[PRICING] Base price: " << basePrice << " x " << quantity
        << " = " << baseTotal << "\n";
    out << "[PRICING] Emergency relief pricing applied: 20% reduction\n";
    out << "[PRICING] Discount amount: " << (baseTotal - finalTotal);
    return out.str();
>>>>>>> 07cba5d (Added inventory policy and connected it to core, also disaster factory and enhanced pricing system)
}
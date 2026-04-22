#include "../../include/pricing/StandardPricing.h"
#include <sstream>

double StandardPricing::calculatePrice(double basePrice, int quantity) {
    return basePrice * quantity;
}

std::string StandardPricing::getStrategyName() const {
    return "StandardPricing";
}

std::string StandardPricing::getPricingExplanation(double basePrice, int quantity) const {
    std::ostringstream out;
    out << "[PRICING] Strategy Applied: StandardPricing\n";
    out << "[PRICING] Base price: " << basePrice << " x " << quantity
        << " = " << (basePrice * quantity) << "\n";
    out << "[PRICING] No additional adjustment applied";
    return out.str();
}
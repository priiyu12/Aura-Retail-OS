#include "../../include/pricing/DiscountPricing.h"
<<<<<<< HEAD

double DiscountPricing::calculatePrice(double basePrice, int quantity) {
    return (basePrice * quantity) * 0.90;
=======
#include <sstream>

double DiscountPricing::calculatePrice(double basePrice, int quantity) {
    return (basePrice * quantity) * 0.90;
}

std::string DiscountPricing::getStrategyName() const {
    return "DiscountPricing";
}

std::string DiscountPricing::getPricingExplanation(double basePrice, int quantity) const {
    double baseTotal = basePrice * quantity;
    double finalTotal = baseTotal * 0.90;

    std::ostringstream out;
    out << "[PRICING] Strategy Applied: DiscountPricing\n";
    out << "[PRICING] Base price: " << basePrice << " x " << quantity
        << " = " << baseTotal << "\n";
    out << "[PRICING] Student discount applied: 10%\n";
    out << "[PRICING] Discount amount: " << (baseTotal - finalTotal);
    return out.str();
>>>>>>> 07cba5d (Added inventory policy and connected it to core, also disaster factory and enhanced pricing system)
}
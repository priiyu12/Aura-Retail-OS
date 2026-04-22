#ifndef DISCOUNT_PRICING_H
#define DISCOUNT_PRICING_H

#include "PricingStrategy.h"

class DiscountPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
<<<<<<< HEAD
=======
    std::string getStrategyName() const override;
    std::string getPricingExplanation(double basePrice, int quantity) const override;
>>>>>>> 07cba5d (Added inventory policy and connected it to core, also disaster factory and enhanced pricing system)
};

#endif
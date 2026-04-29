#ifndef DISCOUNT_PRICING_H
#define DISCOUNT_PRICING_H

#include "PricingStrategy.h"
#include <string>

class DiscountPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
    std::string getStrategyName() const override;
    std::string getPricingExplanation(double basePrice, int quantity) const override;
};

#endif
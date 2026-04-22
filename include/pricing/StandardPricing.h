#ifndef STANDARD_PRICING_H
#define STANDARD_PRICING_H

#include "PricingStrategy.h"

class StandardPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
    std::string getStrategyName() const override;
    std::string getPricingExplanation(double basePrice, int quantity) const override;
};

#endif
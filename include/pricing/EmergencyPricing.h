#ifndef EMERGENCY_PRICING_H
#define EMERGENCY_PRICING_H

#include "PricingStrategy.h"
#include <string>

class EmergencyPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
    std::string getStrategyName() const override;
    std::string getPricingExplanation(double basePrice, int quantity) const override;
};

#endif
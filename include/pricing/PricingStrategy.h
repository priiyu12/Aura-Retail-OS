#ifndef PRICING_STRATEGY_H
#define PRICING_STRATEGY_H

#include <string>

class PricingStrategy {
public:
    virtual double calculatePrice(double basePrice, int quantity) = 0;
    virtual std::string getStrategyName() const = 0;
    virtual std::string getPricingExplanation(double basePrice, int quantity) const = 0;
    virtual ~PricingStrategy() = default;
};

#endif
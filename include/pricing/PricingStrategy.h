#ifndef PRICING_STRATEGY_H
#define PRICING_STRATEGY_H

class PricingStrategy {
public:
    virtual double calculatePrice(double basePrice, int quantity) = 0;
    virtual ~PricingStrategy() = default;
};

#endif
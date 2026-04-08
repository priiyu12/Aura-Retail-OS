#ifndef STANDARD_PRICING_H
#define STANDARD_PRICING_H

#include "PricingStrategy.h"

class StandardPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
};

#endif
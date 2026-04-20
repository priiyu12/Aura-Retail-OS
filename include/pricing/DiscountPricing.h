#ifndef DISCOUNT_PRICING_H
#define DISCOUNT_PRICING_H

#include "PricingStrategy.h"

class DiscountPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
};

#endif
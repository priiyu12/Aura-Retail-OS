#ifndef EMERGENCY_PRICING_H
#define EMERGENCY_PRICING_H

#include "PricingStrategy.h"

class EmergencyPricing : public PricingStrategy {
public:
    double calculatePrice(double basePrice, int quantity) override;
};

#endif
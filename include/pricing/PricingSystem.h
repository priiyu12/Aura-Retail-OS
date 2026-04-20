#ifndef PRICING_SYSTEM_H
#define PRICING_SYSTEM_H

#include "PricingStrategy.h"

class PricingSystem {
private:
    PricingStrategy* strategy;

public:
    PricingSystem(PricingStrategy* strategy = nullptr);

    void setStrategy(PricingStrategy* strategy);
    double computePrice(double basePrice, int quantity);
};

#endif
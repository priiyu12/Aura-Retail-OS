#include "../../include/pricing/PricingSystem.h"

PricingSystem::PricingSystem(PricingStrategy* strategy) : strategy(strategy) {}

void PricingSystem::setStrategy(PricingStrategy* strategy) {
    this->strategy = strategy;
}

double PricingSystem::computePrice(double basePrice, int quantity) {
    if (strategy == nullptr) return 0.0;
    return strategy->calculatePrice(basePrice, quantity);
}
#include "../../include/pricing/PricingSystem.h"

PricingSystem::PricingSystem(PricingStrategy* strategy) : strategy(strategy) {}

void PricingSystem::setStrategy(PricingStrategy* strategy) {
    this->strategy = strategy;
}

double PricingSystem::computePrice(double basePrice, int quantity) {
    if (strategy == nullptr) return 0.0;
    return strategy->calculatePrice(basePrice, quantity);
}

std::string PricingSystem::getStrategyName() const {
    if (strategy == nullptr) return "NoStrategy";
    return strategy->getStrategyName();
}

std::string PricingSystem::getPricingExplanation(double basePrice, int quantity) const {
    if (strategy == nullptr) return "[PRICING] No pricing strategy active.";
    return strategy->getPricingExplanation(basePrice, quantity);
}
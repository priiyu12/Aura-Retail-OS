#include "../../include/pricing/EmergencyPricing.h"

double EmergencyPricing::calculatePrice(double basePrice, int quantity) {
    return (basePrice * quantity) * 0.80;
}
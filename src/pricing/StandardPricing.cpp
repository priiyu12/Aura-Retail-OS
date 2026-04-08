#include "../../include/pricing/StandardPricing.h"

double StandardPricing::calculatePrice(double basePrice, int quantity) {
    return basePrice * quantity;
}
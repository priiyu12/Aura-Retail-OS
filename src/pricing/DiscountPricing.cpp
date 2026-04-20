#include "../../include/pricing/DiscountPricing.h"

double DiscountPricing::calculatePrice(double basePrice, int quantity) {
    return (basePrice * quantity) * 0.90;
}
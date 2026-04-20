#include "../../include/inventory/Bundle.h"

Bundle::Bundle() : bundleId(0), name("") {}

Bundle::Bundle(int bundleId,
               const std::string& name,
               const std::vector<int>& productIds,
               const std::vector<int>& quantities)
    : bundleId(bundleId), name(name), productIds(productIds), quantities(quantities) {}

int Bundle::getBundleId() const { return bundleId; }
std::string Bundle::getName() const { return name; }
std::vector<int> Bundle::getProductIds() const { return productIds; }
std::vector<int> Bundle::getQuantities() const { return quantities; }
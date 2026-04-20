#ifndef KIOSK_FACTORY_H
#define KIOSK_FACTORY_H

#include <string>
#include "../inventory/InventorySystem.h"
#include "../pricing/PricingStrategy.h"

class KioskFactory {
public:
    virtual void setupInventory(InventorySystem& inventory) = 0;
    virtual PricingStrategy* createPricingStrategy() = 0;
    virtual std::string getKioskType() const = 0;
    virtual ~KioskFactory() = default;
};

#endif
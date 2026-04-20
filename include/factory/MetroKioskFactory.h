#ifndef METRO_KIOSK_FACTORY_H
#define METRO_KIOSK_FACTORY_H

#include "KioskFactory.h"

class MetroKioskFactory : public KioskFactory {
public:
    void setupInventory(InventorySystem& inventory) override;
    PricingStrategy* createPricingStrategy() override;
    std::string getKioskType() const override;
};

#endif
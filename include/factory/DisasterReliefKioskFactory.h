#ifndef DISASTER_RELIEF_KIOSK_FACTORY_H
#define DISASTER_RELIEF_KIOSK_FACTORY_H

#include "KioskFactory.h"

class DisasterReliefKioskFactory : public KioskFactory {
public:
    void setupInventory(InventorySystem& inventory) override;
    PricingStrategy* createPricingStrategy() override;
    std::string getKioskType() const override;
};

#endif
#ifndef HOSPITAL_KIOSK_FACTORY_H
#define HOSPITAL_KIOSK_FACTORY_H

#include "KioskFactory.h"

class HospitalKioskFactory : public KioskFactory {
public:
    void setupInventory(InventorySystem& inventory) override;
    PricingStrategy* createPricingStrategy() override;
    std::string getKioskType() const override;
};

#endif
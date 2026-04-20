#ifndef UNIVERSITY_KIOSK_FACTORY_H
#define UNIVERSITY_KIOSK_FACTORY_H

#include "KioskFactory.h"

class UniversityKioskFactory : public KioskFactory {
public:
    void setupInventory(InventorySystem& inventory) override;
    PricingStrategy* createPricingStrategy() override;
    std::string getKioskType() const override;
};

#endif
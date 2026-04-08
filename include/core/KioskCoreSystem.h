#ifndef KIOSK_CORE_SYSTEM_H
#define KIOSK_CORE_SYSTEM_H

#include <string>
#include "../inventory/InventorySystem.h"
#include "../payment/PaymentSystem.h"
#include "../hardware/HardwareLayer.h"
#include "../pricing/PricingSystem.h"
#include "../events/EventBus.h"

class KioskCoreSystem {
private:
    InventorySystem* inventorySystem;
    PaymentSystem* paymentSystem;
    HardwareLayer* hardwareLayer;
    PricingSystem* pricingSystem;
    EventBus* eventBus;

public:
    KioskCoreSystem(InventorySystem* inventorySystem,
                    PaymentSystem* paymentSystem,
                    HardwareLayer* hardwareLayer,
                    PricingSystem* pricingSystem,
                    EventBus* eventBus);

    bool handlePurchase(int productId, int quantity, const std::string& paymentMethod);
    void handleDiagnostics();
    void showProducts() const;
};

#endif
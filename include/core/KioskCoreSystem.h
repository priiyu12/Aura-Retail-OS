#ifndef KIOSK_CORE_SYSTEM_H
#define KIOSK_CORE_SYSTEM_H

#include <string>
#include "../inventory/InventorySystem.h"
#include "../inventory/InventoryPolicy.h"
#include "../payment/PaymentSystem.h"
#include "../hardware/HardwareLayer.h"
#include "../pricing/PricingSystem.h"
#include "../events/EventBus.h"
#include "../transaction/TransactionManager.h"

class KioskCoreSystem {
private:
    InventorySystem* inventorySystem;
    InventoryPolicy* inventoryPolicy;
    PaymentSystem* paymentSystem;
    HardwareLayer* hardwareLayer;
    PricingSystem* pricingSystem;
    EventBus* eventBus;
    TransactionManager* transactionManager;
    std::string kioskType;

public:
    KioskCoreSystem(InventorySystem* inventorySystem,
                    InventoryPolicy* inventoryPolicy,
                    PaymentSystem* paymentSystem,
                    HardwareLayer* hardwareLayer,
                    PricingSystem* pricingSystem,
                    EventBus* eventBus,
                    TransactionManager* transactionManager,
                    const std::string& kioskType);

    bool handlePurchase(int productId, int quantity, const std::string& paymentMethod);
    void handleRestock(int productId, int quantity);
    void handleDiagnostics();
    void showProducts() const;
    void showTransactionHistory() const;
    std::string getKioskType() const;
};

#endif
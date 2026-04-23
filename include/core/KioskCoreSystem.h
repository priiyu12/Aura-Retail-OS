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
#include "../state/KioskState.h"
#include "../core/DecisionMediator.h"
#include "../transaction/TransactionCaretaker.h"
#include "../hardware/FailureHandler.h"

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

    KioskState* kioskState;
    DecisionMediator* decisionMediator;
    TransactionCaretaker* caretaker;
    FailureHandler* failureHandler;

public:
    KioskCoreSystem(InventorySystem* inventorySystem,
                    InventoryPolicy* inventoryPolicy,
                    PaymentSystem* paymentSystem,
                    HardwareLayer* hardwareLayer,
                    PricingSystem* pricingSystem,
                    EventBus* eventBus,
                    TransactionManager* transactionManager,
                    const std::string& kioskType,
                    KioskState* kioskState,
                    DecisionMediator* decisionMediator,
                    TransactionCaretaker* caretaker,
                    FailureHandler* failureHandler);

    bool handlePurchase(int productId, int quantity, const std::string& paymentMethod);
    bool handleBundlePurchase(int bundleId, const std::string& paymentMethod);

    void handleRefund(int productId, int quantity);
    void handleRestock(int productId, int quantity);
    void handleDiagnostics();

    void showProducts() const;
    void showTransactionHistory() const;

    std::string getKioskType() const;
    void setState(KioskState* state);
    void setKioskType(const std::string& newKioskType);
};

#endif
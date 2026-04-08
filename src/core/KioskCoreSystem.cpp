#include "../../include/core/KioskCoreSystem.h"
#include "../../include/events/LowStockEvent.h"
#include "../../include/events/HardwareFailureEvent.h"
#include <iostream>

KioskCoreSystem::KioskCoreSystem(InventorySystem* inventorySystem,
                                 PaymentSystem* paymentSystem,
                                 HardwareLayer* hardwareLayer,
                                 PricingSystem* pricingSystem,
                                 EventBus* eventBus)
    : inventorySystem(inventorySystem),
      paymentSystem(paymentSystem),
      hardwareLayer(hardwareLayer),
      pricingSystem(pricingSystem),
      eventBus(eventBus) {}

bool KioskCoreSystem::handlePurchase(int productId, int quantity, const std::string& paymentMethod) {
    std::cout << "[CORE] Purchase request received.\n";

    if (!inventorySystem->checkAvailability(productId, quantity)) {
        std::cout << "[CORE] Product unavailable or insufficient stock.\n";
        return false;
    }

    Product* product = inventorySystem->getProduct(productId);
    if (product == nullptr) {
        std::cout << "[CORE] Product not found.\n";
        return false;
    }

    if (!inventorySystem->reserveItem(productId, quantity)) {
        std::cout << "[CORE] Failed to reserve item.\n";
        return false;
    }

    double totalPrice = pricingSystem->computePrice(product->getBasePrice(), quantity);
    std::cout << "[CORE] Final price: " << totalPrice << "\n";

    if (!paymentSystem->processPayment(totalPrice, paymentMethod)) {
        std::cout << "[CORE] Payment failed. Releasing reserved stock.\n";
        inventorySystem->releaseItem(productId, quantity);
        return false;
    }

    if (!hardwareLayer->dispenseItem(productId, quantity)) {
        std::cout << "[CORE] Hardware failure. Releasing reserved stock.\n";
        inventorySystem->releaseItem(productId, quantity);
        HardwareFailureEvent failureEvent;
        eventBus->publish(failureEvent);
        return false;
    }

    if (!inventorySystem->confirmPurchase(productId, quantity)) {
        std::cout << "[CORE] Failed to confirm purchase.\n";
        return false;
    }

    std::cout << "[CORE] Purchase completed successfully.\n";

    if (inventorySystem->isLowStock(productId)) {
        LowStockEvent lowStockEvent;
        eventBus->publish(lowStockEvent);
    }

    return true;
}

void KioskCoreSystem::handleDiagnostics() {
    hardwareLayer->runDiagnostics();
}

void KioskCoreSystem::showProducts() const {
    inventorySystem->showInventory();
}
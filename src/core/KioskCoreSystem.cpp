#include "../../include/core/KioskCoreSystem.h"
#include "../../include/events/LowStockEvent.h"
#include "../../include/events/HardwareFailureEvent.h"
#include <iostream>

KioskCoreSystem::KioskCoreSystem(InventorySystem* inventorySystem,
                                 PaymentSystem* paymentSystem,
                                 HardwareLayer* hardwareLayer,
                                 PricingSystem* pricingSystem,
                                 EventBus* eventBus,
                                 const std::string& kioskType)
    : inventorySystem(inventorySystem),
      paymentSystem(paymentSystem),
      hardwareLayer(hardwareLayer),
      pricingSystem(pricingSystem),
      eventBus(eventBus),
      kioskType(kioskType) {}

bool KioskCoreSystem::handlePurchase(int productId, int quantity, const std::string& paymentMethod) {
    std::cout << "[CORE] Purchase request received.\n";
    std::cout << "[STATUS] Kiosk Type: " << kioskType << "\n";
    std::cout << "[STATUS] Kiosk Status: ACTIVE\n";

    Product* product = inventorySystem->getProduct(productId);
    if (product == nullptr) {
        std::cout << "[CORE] Product not found.\n";
        return false;
    }

    // Environment-specific rules
    if (kioskType == "Hospital" && productId == 102 && quantity > 2) {
        std::cout << "[POLICY] Hospital kiosk allows maximum 2 units of Prescription Medicine per transaction.\n";
        return false;
    }

    if (kioskType == "Disaster Relief" && quantity > 2) {
        std::cout << "[POLICY] Disaster Relief kiosk allows maximum 2 essential items per transaction.\n";
        return false;
    }

    if (!inventorySystem->checkAvailability(productId, quantity)) {
        std::cout << "[CORE] Product unavailable or insufficient stock.\n";
        return false;
    }

    if (!inventorySystem->reserveItem(productId, quantity)) {
        std::cout << "[CORE] Failed to reserve item.\n";
        return false;
    }

    double totalPrice = pricingSystem->computePrice(product->getBasePrice(), quantity);
    std::cout << "[PRICING] Final price: " << totalPrice << "\n";

    if (!paymentSystem->processPayment(totalPrice, paymentMethod)) {
        std::cout << "[CORE] Payment failed. Reserved stock released.\n";
        inventorySystem->releaseItem(productId, quantity);
        return false;
    }

    if (!hardwareLayer->dispenseItem(productId, quantity)) {
        std::cout << "[RECOVERY] Dispense failed. Reserved stock released safely.\n";
        inventorySystem->releaseItem(productId, quantity);

        HardwareFailureEvent failureEvent(
            "Dispensing failed for product ID " + std::to_string(productId) +
            ". Maintenance unit has been notified."
        );
        eventBus->publish(failureEvent);
        return false;
    }

    if (!inventorySystem->confirmPurchase(productId, quantity)) {
        std::cout << "[CORE] Failed to confirm purchase.\n";
        return false;
    }

    std::cout << "[CORE] Purchase completed successfully.\n";

    if (inventorySystem->isLowStock(productId)) {
        LowStockEvent lowStockEvent(
            "Low stock detected for product ID " + std::to_string(productId) +
            ". Refill recommended."
        );
        eventBus->publish(lowStockEvent);
    }

    // Transaction summary
    std::cout << "\n===== TRANSACTION SUMMARY =====\n";
    std::cout << "Kiosk Type: " << kioskType << "\n";
    std::cout << "Product: " << product->getName() << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Payment Method: " << paymentMethod << "\n";
    std::cout << "Total Price: " << totalPrice << "\n";
    std::cout << "Status: SUCCESS\n";
    std::cout << "===============================\n";

    return true;
}

void KioskCoreSystem::handleDiagnostics() {
    std::cout << "[STATUS] Running diagnostics for " << kioskType << " kiosk...\n";
    hardwareLayer->runDiagnostics();
}

void KioskCoreSystem::handleRestock(int productId, int quantity) {
    inventorySystem->restockItem(productId, quantity);
    std::cout << "[ADMIN] Product " << productId << " restocked by " << quantity << " units.\n";
}

void KioskCoreSystem::showProducts() const {
    inventorySystem->showInventory();
}

std::string KioskCoreSystem::getKioskType() const {
    return kioskType;
}
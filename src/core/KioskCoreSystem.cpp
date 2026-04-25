#include "../../include/core/KioskCoreSystem.h"
#include "../../include/events/LowStockEvent.h"
#include "../../include/events/HardwareFailureEvent.h"
#include <iostream>

KioskCoreSystem::KioskCoreSystem(InventorySystem* inventorySystem,
                                 InventoryPolicy* inventoryPolicy,
                                 PaymentSystem* paymentSystem,
                                 HardwareLayer* hardwareLayer,
                                 PricingSystem* pricingSystem,
                                 EventBus* eventBus,
                                 TransactionManager* transactionManager,
                                 const std::string& kioskType)
    : inventorySystem(inventorySystem),
      inventoryPolicy(inventoryPolicy),
      paymentSystem(paymentSystem),
      hardwareLayer(hardwareLayer),
      pricingSystem(pricingSystem),
      eventBus(eventBus),
      transactionManager(transactionManager),
      kioskType(kioskType) {}

bool KioskCoreSystem::handlePurchase(int productId, int quantity, const std::string& paymentMethod) {
    std::cout << "[CORE] Purchase request received.\n";

    Product* product = inventorySystem->getProduct(productId);
    if (product == nullptr) {
        std::cout << "[CORE] Product not found.\n";
        return false;
    }

    std::string reason;
    if (!inventoryPolicy->validatePurchase(kioskType, *product, quantity, reason)) {
        std::cout << "[POLICY] " << reason << "\n";
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
    int transactionId = transactionManager->createTransaction(
        "PURCHASE", productId, quantity, totalPrice, paymentMethod, "PENDING"
    );

    std::cout << "[PRICING] Final price: " << totalPrice << "\n";

    if (!paymentSystem->processPayment(totalPrice, paymentMethod)) {
        inventorySystem->releaseItem(productId, quantity);
        transactionManager->updateTransactionStatus(transactionId, "FAILED_PAYMENT");
        std::cout << "[CORE] Payment failed. Reserved stock released.\n";
        return false;
    }

    if (!hardwareLayer->dispenseItem(productId, quantity)) {
        inventorySystem->releaseItem(productId, quantity);
        transactionManager->updateTransactionStatus(transactionId, "FAILED_HARDWARE");

        HardwareFailureEvent failureEvent(
            "Dispensing failed for product ID " + std::to_string(productId) +
            ". Reserved stock released. Technician attention required."
        );
        eventBus->publish(failureEvent);

        std::cout << "[RECOVERY] Hardware failure handled safely.\n";
        return false;
    }

    if (!inventorySystem->confirmPurchase(productId, quantity)) {
        transactionManager->updateTransactionStatus(transactionId, "FAILED_CONFIRMATION");
        std::cout << "[CORE] Failed to confirm purchase.\n";
        return false;
    }

    transactionManager->updateTransactionStatus(transactionId, "SUCCESS");
    std::cout << "[CORE] Purchase completed successfully.\n";

    if (inventorySystem->isLowStock(productId)) {
        LowStockEvent lowStockEvent(
            "Low stock detected for product ID " + std::to_string(productId) +
            ". Refill recommended."
        );
        eventBus->publish(lowStockEvent);
    }

    std::cout << "\n===== TRANSACTION SUMMARY =====\n";
    std::cout << "Transaction ID: " << transactionId << "\n";
    std::cout << "Kiosk Type: " << kioskType << "\n";
    std::cout << "Product: " << product->getName() << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Payment Method: " << paymentMethod << "\n";
    std::cout << "Total Price: " << totalPrice << "\n";
    std::cout << "Status: SUCCESS\n";
    std::cout << "===============================\n";

    return true;
}

void KioskCoreSystem::handleRestock(int productId, int quantity) {
    std::string reason;
    if (!inventoryPolicy->validateRestock(quantity, reason)) {
        std::cout << "[ADMIN] " << reason << "\n";
        return;
    }

    inventorySystem->restockItem(productId, quantity);

    int transactionId = transactionManager->createTransaction(
        "RESTOCK", productId, quantity, 0.0, "ADMIN", "SUCCESS"
    );

    std::cout << "[ADMIN] Product " << productId
              << " restocked by " << quantity
              << " units. Transaction ID: " << transactionId << "\n";
}

void KioskCoreSystem::handleDiagnostics() {
    std::cout << "[STATUS] Running diagnostics for " << kioskType << " kiosk...\n";
    hardwareLayer->runDiagnostics();
}

void KioskCoreSystem::showProducts() const {
    inventorySystem->showInventory();
}

void KioskCoreSystem::showTransactionHistory() const {
    transactionManager->showTransactions();
}

std::string KioskCoreSystem::getKioskType() const {
    return kioskType;
}
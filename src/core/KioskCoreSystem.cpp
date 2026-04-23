#include "../../include/core/KioskCoreSystem.h"
#include "../../include/events/LowStockEvent.h"
#include "../../include/events/HardwareFailureEvent.h"
#include "../../include/events/PolicyViolationEvent.h"
#include <iostream>

KioskCoreSystem::KioskCoreSystem(InventorySystem* inventorySystem,
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
                                 FailureHandler* failureHandler)
    : inventorySystem(inventorySystem),
      inventoryPolicy(inventoryPolicy),
      paymentSystem(paymentSystem),
      hardwareLayer(hardwareLayer),
      pricingSystem(pricingSystem),
      eventBus(eventBus),
      transactionManager(transactionManager),
      kioskType(kioskType),
      kioskState(kioskState),
      decisionMediator(decisionMediator),
      caretaker(caretaker),
      failureHandler(failureHandler) {}

bool KioskCoreSystem::handlePurchase(int productId, int quantity, const std::string& paymentMethod) {

    std::cout << "[CORE] Purchase request received.\n";
    std::cout << "[STATUS] Kiosk Type: " << kioskType << "\n";
    std::cout << "[STATUS] Current Mode: " << kioskState->getStateName() << "\n";
    std::cout << "[ENVIRONMENT] " << inventoryPolicy->getEnvironmentNote(kioskType) << "\n";

    if (!decisionMediator->canProcessPurchase(kioskState)) {
        std::string msg = "Purchase blocked because current mode is " + kioskState->getStateName();
        std::cout << "[STATE] " << msg << "\n";

        PolicyViolationEvent violationEvent(msg);
        eventBus->publish(violationEvent);
        return false;
    }

    Product* product = inventorySystem->getProduct(productId);

    if (product == nullptr) {
        std::cout << "[CORE] Product not found.\n";
        return false;
    }

    std::string reason;

    if (!inventoryPolicy->validatePurchase(
            kioskType,
            *product,
            quantity,
            kioskState->getStateName(),
            reason)) {

        std::cout << "[POLICY] " << reason << "\n";
        PolicyViolationEvent violationEvent(reason);
        eventBus->publish(violationEvent);
        return false;
    }

    if (!inventorySystem->checkAvailability(productId, quantity)) {
        std::cout << "[CORE] Product unavailable or insufficient stock.\n";
        return false;
    }

    caretaker->saveSnapshot(
        TransactionSnapshot(
            productId,
            product->getStock(),
            product->getReservedStock()));

    if (!inventorySystem->reserveItem(productId, quantity)) {
        std::cout << "[CORE] Failed to reserve item.\n";
        return false;
    }

    double totalPrice = pricingSystem->computePrice(product->getBasePrice(), quantity);

    int transactionId = transactionManager->createTransaction(
        "PURCHASE",
        productId,
        quantity,
        totalPrice,
        paymentMethod,
        "PENDING");

    std::cout << pricingSystem->getPricingExplanation(product->getBasePrice(), quantity) << "\n";
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

        failureHandler->handle(
            "Dispense failure for product ID " + std::to_string(productId));

        HardwareFailureEvent failureEvent(
            "Dispensing failed for product ID " + std::to_string(productId) +
            ". Reserved stock released safely.");

        eventBus->publish(failureEvent);

        std::cout << "[RECOVERY] Hardware failure handled safely.\n";
        return false;
    }

    if (!inventorySystem->confirmPurchase(productId, quantity)) {

        transactionManager->updateTransactionStatus(
            transactionId,
            "FAILED_CONFIRMATION");

        std::cout << "[CORE] Failed to confirm purchase.\n";
        return false;
    }

    transactionManager->updateTransactionStatus(transactionId, "SUCCESS");

    std::cout << "[CORE] Purchase completed successfully.\n";

    if (inventorySystem->isLowStock(productId)) {

        LowStockEvent lowStockEvent(
            "Low stock detected for product ID " +
            std::to_string(productId) +
            ". Refill recommended.");

        eventBus->publish(lowStockEvent);
    }

    std::cout << "\n===== TRANSACTION SUMMARY =====\n";
    std::cout << "Transaction ID: " << transactionId << "\n";
    std::cout << "Kiosk Type: " << kioskType << "\n";
    std::cout << "Mode: " << kioskState->getStateName() << "\n";
    std::cout << "Product: " << product->getName() << "\n";
    std::cout << "Category: " << product->getCategory() << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Payment Method: " << paymentMethod << "\n";
    std::cout << "Total Price: " << totalPrice << "\n";
    std::cout << "Status: SUCCESS\n";
    std::cout << "===============================\n";

    return true;
}

bool KioskCoreSystem::handleBundlePurchase(int bundleId, const std::string& paymentMethod) {

    std::cout << "[CORE] Bundle purchase request received.\n";
    std::cout << "[STATUS] Kiosk Type: " << kioskType << "\n";
    std::cout << "[STATUS] Current Mode: " << kioskState->getStateName() << "\n";

    if (!decisionMediator->canProcessPurchase(kioskState)) {

        std::string msg =
            "Bundle purchase blocked because current mode is " +
            kioskState->getStateName();

        std::cout << "[STATE] " << msg << "\n";

        PolicyViolationEvent violationEvent(msg);
        eventBus->publish(violationEvent);

        return false;
    }

    Bundle* bundle = inventorySystem->getBundle(bundleId);

    if (bundle == nullptr) {
        std::cout << "[CORE] Bundle not found.\n";
        return false;
    }

    if (!inventorySystem->checkBundleAvailability(bundleId)) {
        std::cout << "[CORE] Bundle unavailable due to insufficient stock.\n";
        return false;
    }

    if (!inventorySystem->reserveBundle(bundleId)) {
        std::cout << "[CORE] Failed to reserve bundle.\n";
        return false;
    }

    double basePrice = inventorySystem->calculateBundleBasePrice(bundleId);
    double totalPrice = pricingSystem->computePrice(basePrice, 1);

    int transactionId = transactionManager->createTransaction(
        "BUNDLE_PURCHASE",
        bundleId,
        1,
        totalPrice,
        paymentMethod,
        "PENDING");

    if (!paymentSystem->processPayment(totalPrice, paymentMethod)) {

        inventorySystem->releaseBundle(bundleId);

        transactionManager->updateTransactionStatus(
            transactionId,
            "FAILED_PAYMENT");

        std::cout << "[CORE] Payment failed.\n";
        return false;
    }

    if (!inventorySystem->confirmBundlePurchase(bundleId)) {

        transactionManager->updateTransactionStatus(
            transactionId,
            "FAILED_CONFIRMATION");

        std::cout << "[CORE] Failed to confirm bundle purchase.\n";
        return false;
    }

    transactionManager->updateTransactionStatus(transactionId, "SUCCESS");

    std::cout << "[CORE] Bundle purchase successful.\n";

    return true;
}

void KioskCoreSystem::handleRefund(int productId, int quantity) {

    inventorySystem->restockItem(productId, quantity);

    int transactionId = transactionManager->createTransaction(
        "REFUND",
        productId,
        quantity,
        0.0,
        "REFUND",
        "SUCCESS");

    std::cout << "[CORE] Refund processed. Transaction ID: "
              << transactionId << "\n";
}

void KioskCoreSystem::handleRestock(int productId, int quantity) {

    if (!decisionMediator->canProcessRestock(kioskState)) {

        std::string msg =
            "Restock blocked because current mode is " +
            kioskState->getStateName();

        std::cout << "[STATE] " << msg << "\n";

        PolicyViolationEvent violationEvent(msg);
        eventBus->publish(violationEvent);

        return;
    }

    std::string reason;

    if (!inventoryPolicy->validateRestock(
            kioskType,
            quantity,
            reason)) {

        std::cout << "[ADMIN] " << reason << "\n";

        PolicyViolationEvent violationEvent(reason);
        eventBus->publish(violationEvent);

        return;
    }

    inventorySystem->restockItem(productId, quantity);

    int transactionId = transactionManager->createTransaction(
        "RESTOCK",
        productId,
        quantity,
        0.0,
        "ADMIN",
        "SUCCESS");

    std::cout << "[ADMIN] Product " << productId
              << " restocked by "
              << quantity
              << " units. Transaction ID: "
              << transactionId << "\n";
}

void KioskCoreSystem::handleDiagnostics() {

    if (!decisionMediator->canRunDiagnostics(kioskState)) {

        std::cout << "[STATE] Diagnostics not allowed in current mode: "
                  << kioskState->getStateName() << "\n";

        return;
    }

    std::cout << "[STATUS] Running diagnostics...\n";

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

void KioskCoreSystem::setState(KioskState* state) {
    kioskState = state;
}

void KioskCoreSystem::setKioskType(const std::string& newKioskType) {
    kioskType = newKioskType;
}
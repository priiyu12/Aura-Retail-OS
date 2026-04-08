#include "../../include/interface/KioskInterface.h"
#include "../../include/core/KioskCoreSystem.h"

KioskInterface::KioskInterface(KioskCoreSystem* coreSystem) : coreSystem(coreSystem) {}

void KioskInterface::purchaseItem(int productId, int quantity, const std::string& paymentMethod) {
    coreSystem->handlePurchase(productId, quantity, paymentMethod);
}

void KioskInterface::runDiagnostics() {
    coreSystem->handleDiagnostics();
}

void KioskInterface::displayProducts() const {
    coreSystem->showProducts();
}
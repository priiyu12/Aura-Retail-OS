#include "../../include/interface/KioskInterface.h"
#include "../../include/core/KioskCoreSystem.h"
#include "../../include/commands/PurchaseCommand.h"
#include "../../include/commands/RestockCommand.h"

KioskInterface::KioskInterface(KioskCoreSystem* coreSystem) : coreSystem(coreSystem) {}

void KioskInterface::purchaseItem(int productId, int quantity, const std::string& paymentMethod) {
    PurchaseCommand command(coreSystem, productId, quantity, paymentMethod);
    command.execute();
}

void KioskInterface::restockInventory(int productId, int quantity) {
    RestockCommand command(coreSystem, productId, quantity);
    command.execute();
}

void KioskInterface::runDiagnostics() {
    coreSystem->handleDiagnostics();
}

void KioskInterface::displayProducts() const {
    coreSystem->showProducts();
}

void KioskInterface::displayTransactionHistory() const {
    coreSystem->showTransactionHistory();
}
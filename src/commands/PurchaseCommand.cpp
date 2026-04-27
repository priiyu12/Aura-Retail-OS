#include "../../include/commands/PurchaseCommand.h"
#include "../../include/core/KioskCoreSystem.h"

PurchaseCommand::PurchaseCommand(KioskCoreSystem* coreSystem,
                                 int productId,
                                 int quantity,
                                 const std::string& paymentMethod)
    : coreSystem(coreSystem),
      productId(productId),
      quantity(quantity),
      paymentMethod(paymentMethod) {}

void PurchaseCommand::execute() {
    coreSystem->handlePurchase(productId, quantity, paymentMethod);
}
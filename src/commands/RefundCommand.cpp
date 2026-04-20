#include "../../include/commands/RefundCommand.h"
#include "../../include/core/KioskCoreSystem.h"

RefundCommand::RefundCommand(KioskCoreSystem* coreSystem, int productId, int quantity)
    : coreSystem(coreSystem), productId(productId), quantity(quantity) {}

void RefundCommand::execute() {
    coreSystem->handleRefund(productId, quantity);
}
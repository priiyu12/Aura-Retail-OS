#include "../../include/commands/RestockCommand.h"
#include "../../include/core/KioskCoreSystem.h"

RestockCommand::RestockCommand(KioskCoreSystem* coreSystem, int productId, int quantity)
    : coreSystem(coreSystem), productId(productId), quantity(quantity) {}

void RestockCommand::execute() {
    coreSystem->handleRestock(productId, quantity);
}

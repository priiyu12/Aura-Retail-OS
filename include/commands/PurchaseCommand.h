#ifndef PURCHASE_COMMAND_H
#define PURCHASE_COMMAND_H

#include <string>
#include "Command.h"

class KioskCoreSystem;

class PurchaseCommand : public Command {
private:
    KioskCoreSystem* coreSystem;
    int productId;
    int quantity;
    std::string paymentMethod;

public:
    PurchaseCommand(KioskCoreSystem* coreSystem,
                    int productId,
                    int quantity,
                    const std::string& paymentMethod);

    void execute() override;
};

#endif
#ifndef REFUND_COMMAND_H
#define REFUND_COMMAND_H

#include "Command.h"

class KioskCoreSystem;

class RefundCommand : public Command {
private:
    KioskCoreSystem* coreSystem;
    int productId;
    int quantity;

public:
    RefundCommand(KioskCoreSystem* coreSystem, int productId, int quantity);
    void execute() override;
};

#endif
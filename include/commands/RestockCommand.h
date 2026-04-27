#ifndef RESTOCK_COMMAND_H
#define RESTOCK_COMMAND_H

#include "Command.h"

class KioskCoreSystem;

class RestockCommand : public Command {
private:
    KioskCoreSystem* coreSystem;
    int productId;
    int quantity;

public:
    RestockCommand(KioskCoreSystem* coreSystem, int productId, int quantity);
    void execute() override;
};

#endif

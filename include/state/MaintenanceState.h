#ifndef MAINTENANCE_STATE_H
#define MAINTENANCE_STATE_H

#include "KioskState.h"

class MaintenanceState : public KioskState {
public:
    bool canPurchase() const override;
    bool canRestock() const override;
    bool canRunDiagnostics() const override;
    std::string getStateName() const override;
};

#endif
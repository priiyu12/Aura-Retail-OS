#ifndef POWER_SAVING_STATE_H
#define POWER_SAVING_STATE_H

#include "KioskState.h"

class PowerSavingState : public KioskState {
public:
    bool canPurchase() const override;
    bool canRestock() const override;
    bool canRunDiagnostics() const override;
    std::string getStateName() const override;
};

#endif
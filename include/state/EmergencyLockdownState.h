#ifndef EMERGENCY_LOCKDOWN_STATE_H
#define EMERGENCY_LOCKDOWN_STATE_H

#include "KioskState.h"

class EmergencyLockdownState : public KioskState {
public:
    bool canPurchase() const override;
    bool canRestock() const override;
    bool canRunDiagnostics() const override;
    std::string getStateName() const override;
};

#endif
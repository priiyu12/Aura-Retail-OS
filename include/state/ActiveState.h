#ifndef ACTIVE_STATE_H
#define ACTIVE_STATE_H

#include "KioskState.h"

class ActiveState : public KioskState {
public:
    bool canPurchase() const override;
    bool canRestock() const override;
    bool canRunDiagnostics() const override;
    std::string getStateName() const override;
};

#endif
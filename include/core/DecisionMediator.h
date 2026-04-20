#ifndef DECISION_MEDIATOR_H
#define DECISION_MEDIATOR_H

#include <string>
#include "../state/KioskState.h"
#include "../pricing/PricingStrategy.h"

class DecisionMediator {
public:
    bool canProcessPurchase(const KioskState* state) const;
    bool canProcessRestock(const KioskState* state) const;
    bool canRunDiagnostics(const KioskState* state) const;
};

#endif
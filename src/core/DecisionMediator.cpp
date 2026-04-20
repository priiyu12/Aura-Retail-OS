#include "../../include/core/DecisionMediator.h"

bool DecisionMediator::canProcessPurchase(const KioskState* state) const {
    return state != nullptr && state->canPurchase();
}

bool DecisionMediator::canProcessRestock(const KioskState* state) const {
    return state != nullptr && state->canRestock();
}

bool DecisionMediator::canRunDiagnostics(const KioskState* state) const {
    return state != nullptr && state->canRunDiagnostics();
}
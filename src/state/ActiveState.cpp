#include "../../include/state/ActiveState.h"

bool ActiveState::canPurchase() const { return true; }
bool ActiveState::canRestock() const { return true; }
bool ActiveState::canRunDiagnostics() const { return true; }
std::string ActiveState::getStateName() const { return "ACTIVE"; }
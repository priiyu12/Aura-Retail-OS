#include "../../include/state/PowerSavingState.h"

bool PowerSavingState::canPurchase() const { return true; }
bool PowerSavingState::canRestock() const { return true; }
bool PowerSavingState::canRunDiagnostics() const { return false; }
std::string PowerSavingState::getStateName() const { return "POWER_SAVING"; }
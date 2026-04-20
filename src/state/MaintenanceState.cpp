#include "../../include/state/MaintenanceState.h"

bool MaintenanceState::canPurchase() const { return false; }
bool MaintenanceState::canRestock() const { return true; }
bool MaintenanceState::canRunDiagnostics() const { return true; }
std::string MaintenanceState::getStateName() const { return "MAINTENANCE"; }
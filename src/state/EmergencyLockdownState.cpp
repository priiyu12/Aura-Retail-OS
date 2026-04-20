#include "../../include/state/EmergencyLockdownState.h"

bool EmergencyLockdownState::canPurchase() const { return false; }
bool EmergencyLockdownState::canRestock() const { return true; }
bool EmergencyLockdownState::canRunDiagnostics() const { return true; }
std::string EmergencyLockdownState::getStateName() const { return "EMERGENCY_LOCKDOWN"; }
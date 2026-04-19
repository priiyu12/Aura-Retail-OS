#include "../../include/hardware/HardwareLayer.h"
#include <iostream>

HardwareLayer::HardwareLayer() : failNextDispense(false), hardwareHealthy(true) {}

bool HardwareLayer::dispenseItem(int productId, int quantity) {
    std::cout << "[HARDWARE] Dispensing product " << productId
              << " x" << quantity << "\n";

    if (failNextDispense) {
        std::cout << "[HARDWARE] Dispensing failed.\n";
        failNextDispense = false;
        hardwareHealthy = false;
        return false;
    }

    std::cout << "[HARDWARE] Dispensing successful.\n";
    hardwareHealthy = true;
    return true;
}

void HardwareLayer::runDiagnostics() {
    if (hardwareHealthy) {
        std::cout << "[HARDWARE] Diagnostics completed. All systems normal.\n";
    } else {
        std::cout << "[HARDWARE] Diagnostics warning: last operation reported a hardware issue.\n";
    }
}

void HardwareLayer::setFailNextDispense(bool fail) {
    failNextDispense = fail;
}

bool HardwareLayer::isHealthy() const {
    return hardwareHealthy;
}
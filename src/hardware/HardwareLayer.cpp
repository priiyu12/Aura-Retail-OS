#include "../../include/hardware/HardwareLayer.h"
#include <iostream>

HardwareLayer::HardwareLayer() : failNextDispense(false) {}

bool HardwareLayer::dispenseItem(int productId, int quantity) {
    std::cout << "[HARDWARE] Dispensing product " << productId
              << " x" << quantity << "\n";

    if (failNextDispense) {
        std::cout << "[HARDWARE] Dispensing failed.\n";
        failNextDispense = false;
        return false;
    }

    std::cout << "[HARDWARE] Dispensing successful.\n";
    return true;
}

void HardwareLayer::runDiagnostics() {
    std::cout << "[HARDWARE] Diagnostics completed. All systems normal.\n";
}

void HardwareLayer::setFailNextDispense(bool fail) {
    failNextDispense = fail;
}
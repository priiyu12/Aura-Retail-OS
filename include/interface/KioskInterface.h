#ifndef KIOSK_INTERFACE_H
#define KIOSK_INTERFACE_H

#include <string>

class KioskCoreSystem;

class KioskInterface {
private:
    KioskCoreSystem* coreSystem;

public:
    KioskInterface(KioskCoreSystem* coreSystem);

    void purchaseItem(int productId, int quantity, const std::string& paymentMethod);
    void runDiagnostics();
    void restockInventory(int productId, int quantity);
    void displayProducts() const;
};

#endif
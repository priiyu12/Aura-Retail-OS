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
    void restockInventory(int productId, int quantity);
    void runDiagnostics();
    void displayProducts() const;
    void displayTransactionHistory() const;
};

#endif
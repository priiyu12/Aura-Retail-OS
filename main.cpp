#include <iostream>
#include <string>

#include "include/models/Product.h"
#include "include/inventory/InventorySystem.h"
#include "include/payment/PaymentSystem.h"
#include "include/hardware/HardwareLayer.h"
#include "include/pricing/StandardPricing.h"
#include "include/pricing/PricingSystem.h"
#include "include/events/EventBus.h"
#include "include/monitoring/CityMonitoringSystem.h"
#include "include/core/KioskCoreSystem.h"
#include "include/interface/KioskInterface.h"

void setupHospitalKiosk(InventorySystem& inventory) {
    inventory.addProduct(Product(101, "Paracetamol", 20.0, 10, 2));
    inventory.addProduct(Product(102, "Prescription Medicine", 120.0, 5, 1));
    inventory.addProduct(Product(103, "Sanitizer", 50.0, 8, 2));
}

void setupMetroKiosk(InventorySystem& inventory) {
    inventory.addProduct(Product(201, "Water Bottle", 20.0, 15, 3));
    inventory.addProduct(Product(202, "Snack Pack", 35.0, 10, 2));
    inventory.addProduct(Product(203, "Umbrella", 150.0, 4, 1));
}

void setupUniversityKiosk(InventorySystem& inventory) {
    inventory.addProduct(Product(301, "Earphones", 500.0, 6, 1));
    inventory.addProduct(Product(302, "Notebook", 40.0, 12, 2));
    inventory.addProduct(Product(303, "Charger", 700.0, 5, 1));
}

void setupDisasterReliefKiosk(InventorySystem& inventory) {
    inventory.addProduct(Product(401, "Emergency Kit", 250.0, 6, 2));
    inventory.addProduct(Product(402, "Water Pack", 80.0, 10, 2));
    inventory.addProduct(Product(403, "First Aid Box", 180.0, 5, 1));
}

void loadKioskProducts(int choice, InventorySystem& inventory) {
    switch (choice) {
        case 1:
            setupHospitalKiosk(inventory);
            std::cout << "\n[SETUP] Hospital kiosk loaded.\n";
            break;
        case 2:
            setupMetroKiosk(inventory);
            std::cout << "\n[SETUP] Metro kiosk loaded.\n";
            break;
        case 3:
            setupUniversityKiosk(inventory);
            std::cout << "\n[SETUP] University kiosk loaded.\n";
            break;
        case 4:
            setupDisasterReliefKiosk(inventory);
            std::cout << "\n[SETUP] Disaster Relief kiosk loaded.\n";
            break;
        default:
            std::cout << "\nInvalid choice. Defaulting to Metro kiosk.\n";
            setupMetroKiosk(inventory);
            break;
    }
}

int main() {
    InventorySystem inventory;
    PaymentSystem payment;
    HardwareLayer hardware;
    StandardPricing standardPricing;
    PricingSystem pricing(&standardPricing);
    EventBus eventBus;
    CityMonitoringSystem monitoring;

    eventBus.subscribe(&monitoring);

    int kioskChoice;
    std::cout << "===== Zephyrus Retail OS =====\n";
    std::cout << "Select kiosk type:\n";
    std::cout << "1. Hospital\n";
    std::cout << "2. Metro\n";
    std::cout << "3. University\n";
    std::cout << "4. Disaster Relief\n";
    std::cout << "Enter choice: ";
    std::cin >> kioskChoice;

    loadKioskProducts(kioskChoice, inventory);

    KioskCoreSystem core(&inventory, &payment, &hardware, &pricing, &eventBus);
    KioskInterface kiosk(&core);

    int option;
    do {
        std::cout << "\n===== Menu =====\n";
        std::cout << "1. Show Products\n";
        std::cout << "2. Purchase Product\n";
        std::cout << "3. Run Diagnostics\n";
        std::cout << "4. Simulate Hardware Failure on Next Dispense\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter option: ";
        std::cin >> option;

        if (option == 1) {
            kiosk.displayProducts();
        } else if (option == 2) {
            int productId, quantity;
            std::string paymentMethod;

            kiosk.displayProducts();

            std::cout << "\nEnter product ID: ";
            std::cin >> productId;

            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            std::cout << "Enter payment method (UPI/Card/Wallet): ";
            std::cin >> paymentMethod;

            kiosk.purchaseItem(productId, quantity, paymentMethod);
        } else if (option == 3) {
            kiosk.runDiagnostics();
        } else if (option == 4) {
            hardware.setFailNextDispense(true);
            std::cout << "[TEST] Next dispense will fail.\n";
        } else if (option == 0) {
            std::cout << "Exiting system.\n";
        } else {
            std::cout << "Invalid option.\n";
        }

    } while (option != 0);

    return 0;
}
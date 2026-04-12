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

void initializeAllKiosks(
    InventorySystem& hospitalInventory,
    InventorySystem& metroInventory,
    InventorySystem& universityInventory,
    InventorySystem& disasterInventory
) {
    setupHospitalKiosk(hospitalInventory);
    setupMetroKiosk(metroInventory);
    setupUniversityKiosk(universityInventory);
    setupDisasterReliefKiosk(disasterInventory);
}

InventorySystem* getInventoryByChoice(
    int choice,
    InventorySystem& hospitalInventory,
    InventorySystem& metroInventory,
    InventorySystem& universityInventory,
    InventorySystem& disasterInventory
) {
    switch (choice) {
        case 1: return &hospitalInventory;
        case 2: return &metroInventory;
        case 3: return &universityInventory;
        case 4: return &disasterInventory;
        default: return &metroInventory;
    }
}

std::string getKioskTypeByChoice(int choice) {
    switch (choice) {
        case 1: return "Hospital";
        case 2: return "Metro";
        case 3: return "University";
        case 4: return "Disaster Relief";
        default: return "Metro";
    }
}

int main() {
    PaymentSystem payment;
    HardwareLayer hardware;
    StandardPricing standardPricing;
    PricingSystem pricing(&standardPricing);
    EventBus eventBus;
    CityMonitoringSystem monitoring;

    eventBus.subscribe(&monitoring);

    // Shared inventories for all modes
    InventorySystem hospitalInventory;
    InventorySystem metroInventory;
    InventorySystem universityInventory;
    InventorySystem disasterInventory;

    initializeAllKiosks(
        hospitalInventory,
        metroInventory,
        universityInventory,
        disasterInventory
    );

    int mainChoice;

    do {
        std::cout << "\n===== Zephyrus Retail OS =====\n";
        std::cout << "1. User Mode\n";
        std::cout << "2. Admin Mode\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> mainChoice;

        if (mainChoice == 1) {
            int kioskChoice;
            std::cout << "\nSelect kiosk type:\n";
            std::cout << "1. Hospital\n";
            std::cout << "2. Metro\n";
            std::cout << "3. University\n";
            std::cout << "4. Disaster Relief\n";
            std::cout << "Enter choice: ";
            std::cin >> kioskChoice;

            InventorySystem* inventory = getInventoryByChoice(
                kioskChoice,
                hospitalInventory,
                metroInventory,
                universityInventory,
                disasterInventory
            );

            std::string kioskType = getKioskTypeByChoice(kioskChoice);

            std::cout << "\n[SETUP] " << kioskType << " kiosk selected.\n";

            KioskCoreSystem core(inventory, &payment, &hardware, &pricing, &eventBus, kioskType);
            KioskInterface kiosk(&core);

            int userOption;
            do {
                std::cout << "\n===== USER MODE =====\n";
                std::cout << "1. Show Products\n";
                std::cout << "2. Purchase Product\n";
                std::cout << "0. Back\n";
                std::cout << "Enter option: ";
                std::cin >> userOption;

                if (userOption == 1) {
                    kiosk.displayProducts();
                }
                else if (userOption == 2) {
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
                }
                else if (userOption == 0) {
                    std::cout << "Returning to main menu...\n";
                }
                else {
                    std::cout << "Invalid option.\n";
                }

            } while (userOption != 0);
        }

        else if (mainChoice == 2) {
            std::string password;
            std::cout << "\nEnter admin password: ";
            std::cin >> password;

            if (password != "1234") {
                std::cout << "[ADMIN] Incorrect password. Access denied.\n";
                continue;
            }

            std::cout << "[ADMIN] Login successful.\n";

            int kioskChoice;
            std::cout << "\nSelect kiosk type for admin operations:\n";
            std::cout << "1. Hospital\n";
            std::cout << "2. Metro\n";
            std::cout << "3. University\n";
            std::cout << "4. Disaster Relief\n";
            std::cout << "Enter choice: ";
            std::cin >> kioskChoice;

            InventorySystem* inventory = getInventoryByChoice(
                kioskChoice,
                hospitalInventory,
                metroInventory,
                universityInventory,
                disasterInventory
            );

            std::string kioskType = getKioskTypeByChoice(kioskChoice);

            std::cout << "\n[SETUP] " << kioskType << " kiosk selected.\n";

            KioskCoreSystem core(inventory, &payment, &hardware, &pricing, &eventBus, kioskType);
            KioskInterface kiosk(&core);

            int adminOption;
            do {
                std::cout << "\n===== ADMIN MODE =====\n";
                std::cout << "1. Show Inventory\n";
                std::cout << "2. Restock Item\n";
                std::cout << "3. Run Diagnostics\n";
                std::cout << "4. Simulate Hardware Failure on Next Dispense\n";
                std::cout << "0. Back\n";
                std::cout << "Enter option: ";
                std::cin >> adminOption;

                if (adminOption == 1) {
                    kiosk.displayProducts();
                }
                else if (adminOption == 2) {
                    int productId, quantity;

                    kiosk.displayProducts();

                    std::cout << "\nEnter product ID to restock: ";
                    std::cin >> productId;

                    std::cout << "Enter quantity to add: ";
                    std::cin >> quantity;

                    kiosk.restockInventory(productId, quantity);
                }
                else if (adminOption == 3) {
                    kiosk.runDiagnostics();
                }
                else if (adminOption == 4) {
                    hardware.setFailNextDispense(true);
                    std::cout << "[TEST] Next dispense will fail.\n";
                }
                else if (adminOption == 0) {
                    std::cout << "Returning to main menu...\n";
                }
                else {
                    std::cout << "Invalid option.\n";
                }

            } while (adminOption != 0);
        }

        else if (mainChoice == 0) {
            std::cout << "Exiting system.\n";
        }

        else {
            std::cout << "Invalid choice.\n";
        }

    } while (mainChoice != 0);

    return 0;
}
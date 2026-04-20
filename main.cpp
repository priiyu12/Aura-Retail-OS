#include <iostream>
#include <string>

#include "include/inventory/InventorySystem.h"
#include "include/inventory/InventoryPolicy.h"
#include "include/payment/PaymentSystem.h"
#include "include/hardware/HardwareLayer.h"
#include "include/pricing/PricingSystem.h"
#include "include/pricing/PricingStrategy.h"
#include "include/events/EventBus.h"
#include "include/monitoring/CityMonitoringSystem.h"
#include "include/core/KioskCoreSystem.h"
#include "include/interface/KioskInterface.h"
#include "include/transaction/TransactionManager.h"
#include "include/transaction/TransactionCaretaker.h"

#include "include/factory/KioskFactory.h"
#include "include/factory/HospitalKioskFactory.h"
#include "include/factory/MetroKioskFactory.h"
#include "include/factory/UniversityKioskFactory.h"
#include "include/factory/DisasterReliefKioskFactory.h"

#include "include/state/ActiveState.h"
#include "include/state/PowerSavingState.h"
#include "include/state/MaintenanceState.h"
#include "include/state/EmergencyLockdownState.h"

#include "include/core/DecisionMediator.h"
#include "include/core/CentralRegistry.h"
#include "include/hardware/FailureHandler.h"

int main() {
    InventorySystem inventory;
    InventoryPolicy policy;
    PaymentSystem payment;
    HardwareLayer hardware;
    EventBus eventBus;
    CityMonitoringSystem monitoring;
    TransactionManager transactionManager;
    TransactionCaretaker caretaker;
    DecisionMediator mediator;

    eventBus.subscribe(&monitoring);

    std::cout << "===== Zephyrus Retail OS =====\n";
    std::cout << "Select kiosk type:\n";
    std::cout << "1. Hospital\n";
    std::cout << "2. Metro\n";
    std::cout << "3. University\n";
    std::cout << "4. Disaster Relief\n";
    std::cout << "Enter choice: ";

    int kioskChoice;
    std::cin >> kioskChoice;

    KioskFactory* factory = nullptr;

    switch (kioskChoice) {
        case 1: factory = new HospitalKioskFactory(); break;
        case 2: factory = new MetroKioskFactory(); break;
        case 3: factory = new UniversityKioskFactory(); break;
        case 4: factory = new DisasterReliefKioskFactory(); break;
        default: factory = new MetroKioskFactory(); break;
    }

    factory->setupInventory(inventory);
    PricingStrategy* strategy = factory->createPricingStrategy();
    PricingSystem pricing(strategy);
    std::string kioskType = factory->getKioskType();

    CentralRegistry::getInstance().setActiveKioskType(kioskType);
    CentralRegistry::getInstance().setCurrentMode("ACTIVE");

    ActiveState activeState;
    PowerSavingState powerSavingState;
    MaintenanceState maintenanceState;
    EmergencyLockdownState emergencyLockdownState;

    KioskState* currentState = &activeState;

    RetryHandler retryHandler;
    RecalibrationHandler recalibrationHandler;
    TechnicianAlertHandler technicianAlertHandler;

    retryHandler.setNext(&recalibrationHandler);
    recalibrationHandler.setNext(&technicianAlertHandler);

    KioskCoreSystem core(
        &inventory,
        &policy,
        &payment,
        &hardware,
        &pricing,
        &eventBus,
        &transactionManager,
        kioskType,
        currentState,
        &mediator,
        &caretaker,
        &retryHandler
    );

    KioskInterface kiosk(&core);

    int mainChoice;
    do {
        std::cout << "\n===== MAIN MENU =====\n";
        std::cout << "1. User Mode\n";
        std::cout << "2. Admin Mode\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> mainChoice;

        if (mainChoice == 1) {
            int userOption;
            do {
                std::cout << "\n===== USER MODE =====\n";
                std::cout << "1. Show Products\n";
                std::cout << "2. Simulate Hardware Failure on Next Dispense\n";
                std::cout << "3. Purchase Product\n";
                std::cout << "0. Back\n";
                std::cout << "Enter option: ";
                std::cin >> userOption;

                if (userOption == 1) {
                    kiosk.displayProducts();
                } 
                else if (userOption == 2) {
                    hardware.setFailNextDispense(true);
                    std::cout << "[TEST] Next dispense will fail.\n";
                } 
                else if (userOption == 3) {
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

            int adminOption;
            do {
                std::cout << "\n===== ADMIN MODE =====\n";
                std::cout << "1. Show Inventory\n";
                std::cout << "2. Restock Item\n";
                std::cout << "3. Run Diagnostics\n";
                std::cout << "4. Show Transaction History\n";
                std::cout << "5. Change System Mode\n";
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
                    kiosk.displayTransactionHistory();
                } 
                else if (adminOption == 5) {
                    int modeChoice;
                    std::cout << "\nSelect system mode:\n";
                    std::cout << "1. Active\n";
                    std::cout << "2. Power Saving\n";
                    std::cout << "3. Maintenance\n";
                    std::cout << "4. Emergency Lockdown\n";
                    std::cout << "Enter choice: ";
                    std::cin >> modeChoice;

                    if (modeChoice == 1) {
                        currentState = &activeState;
                        CentralRegistry::getInstance().setCurrentMode("ACTIVE");
                    } else if (modeChoice == 2) {
                        currentState = &powerSavingState;
                        CentralRegistry::getInstance().setCurrentMode("POWER_SAVING");
                    } else if (modeChoice == 3) {
                        currentState = &maintenanceState;
                        CentralRegistry::getInstance().setCurrentMode("MAINTENANCE");
                    } else if (modeChoice == 4) {
                        currentState = &emergencyLockdownState;
                        CentralRegistry::getInstance().setCurrentMode("EMERGENCY_LOCKDOWN");
                    } else {
                        std::cout << "Invalid mode choice.\n";
                        continue;
                    }

                    core.setState(currentState);
                    std::cout << "[ADMIN] System mode changed to: "
                              << currentState->getStateName() << "\n";
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
            std::cout << "Invalid option.\n";
        }

    } while (mainChoice != 0);

    delete factory;
    delete strategy;

    return 0;
}
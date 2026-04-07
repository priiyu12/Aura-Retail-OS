#include "../../include/payment/PaymentSystem.h"
#include <iostream>

bool PaymentSystem::processPayment(double amount, const std::string& paymentMethod) {
    std::cout << "[PAYMENT] Processing " << paymentMethod
              << " payment of amount: " << amount << "\n";

    if (paymentMethod != "UPI" && paymentMethod != "Card" && paymentMethod != "Wallet") {
        std::cout << "[PAYMENT] Invalid payment method.\n";
        return false;
    }

    std::cout << "[PAYMENT] Payment successful.\n";
    return true;
}
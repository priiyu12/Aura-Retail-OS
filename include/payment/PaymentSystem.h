#ifndef PAYMENT_SYSTEM_H
#define PAYMENT_SYSTEM_H

#include <string>

class PaymentSystem {
public:
    bool processPayment(double amount, const std::string& paymentMethod);
};

#endif
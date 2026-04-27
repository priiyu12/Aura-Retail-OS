#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    int transactionId;
    std::string type;
    int productId;
    int quantity;
    double amount;
    std::string paymentMethod;
    std::string status;

public:
    Transaction();
    Transaction(int transactionId,
                const std::string& type,
                int productId,
                int quantity,
                double amount,
                const std::string& paymentMethod,
                const std::string& status);

    int getTransactionId() const;
    std::string getType() const;
    int getProductId() const;
    int getQuantity() const;
    double getAmount() const;
    std::string getPaymentMethod() const;
    std::string getStatus() const;

    void setStatus(const std::string& status);
};

#endif

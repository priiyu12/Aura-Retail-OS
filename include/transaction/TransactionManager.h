#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <vector>
#include "../models/Transaction.h"

class TransactionManager {
private:
    std::vector<Transaction> transactions;
    int nextTransactionId;

public:
    TransactionManager();

    int createTransaction(const std::string& type,
                          int productId,
                          int quantity,
                          double amount,
                          const std::string& paymentMethod,
                          const std::string& status);

    void updateTransactionStatus(int transactionId, const std::string& status);
    void showTransactions() const;
};

#endif

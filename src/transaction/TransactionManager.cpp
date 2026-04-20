#include "../../include/transaction/TransactionManager.h"
#include <iostream>

TransactionManager::TransactionManager() : nextTransactionId(1) {}

int TransactionManager::createTransaction(const std::string& type,
                                          int productId,
                                          int quantity,
                                          double amount,
                                          const std::string& paymentMethod,
                                          const std::string& status) {
    Transaction tx(nextTransactionId, type, productId, quantity, amount, paymentMethod, status);
    transactions.push_back(tx);
    return nextTransactionId++;
}

void TransactionManager::updateTransactionStatus(int transactionId, const std::string& status) {
    for (auto& tx : transactions) {
        if (tx.getTransactionId() == transactionId) {
            tx.setStatus(status);
            return;
        }
    }
}

void TransactionManager::showTransactions() const {
    std::cout << "\n===== TRANSACTION HISTORY =====\n";
    if (transactions.empty()) {
        std::cout << "No transactions recorded.\n";
        return;
    }

    for (const auto& tx : transactions) {
        std::cout << "ID: " << tx.getTransactionId()
                  << " | Type: " << tx.getType()
                  << " | Product ID: " << tx.getProductId()
                  << " | Qty: " << tx.getQuantity()
                  << " | Amount: " << tx.getAmount()
                  << " | Method: " << tx.getPaymentMethod()
                  << " | Status: " << tx.getStatus()
                  << "\n";
    }
}
const std::vector<Transaction>& TransactionManager::getTransactions() const {
    return transactions;
}
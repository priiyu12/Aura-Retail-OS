#include "../../include/persistence/TransactionStorage.h"
#include "../../include/models/Transaction.h"
#include <fstream>
#include <iostream>
#include <vector>

bool TransactionStorage::saveTransactions(const TransactionManager& manager, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "[PERSISTENCE] Failed to open transaction file for writing.\n";
        return false;
    }

    file << "transactionId,type,productId,quantity,amount,paymentMethod,status\n";

    const std::vector<Transaction>& transactions =
        const_cast<TransactionManager&>(manager).getTransactions();

    for (const auto& tx : transactions) {
        file << tx.getTransactionId() << ","
             << tx.getType() << ","
             << tx.getProductId() << ","
             << tx.getQuantity() << ","
             << tx.getAmount() << ","
             << tx.getPaymentMethod() << ","
             << tx.getStatus() << "\n";
    }

    file.close();
    std::cout << "[PERSISTENCE] Transactions saved to " << filename << "\n";
    return true;
}
#ifndef TRANSACTION_STORAGE_H
#define TRANSACTION_STORAGE_H

#include <string>
#include "../transaction/TransactionManager.h"

class TransactionStorage {
public:
    bool saveTransactions(const TransactionManager& manager, const std::string& filename) const;
};

#endif
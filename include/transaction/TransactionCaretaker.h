#ifndef TRANSACTION_CARETAKER_H
#define TRANSACTION_CARETAKER_H

#include <vector>
#include "TransactionSnapshot.h"

class TransactionCaretaker {
private:
    std::vector<TransactionSnapshot> snapshots;

public:
    void saveSnapshot(const TransactionSnapshot& snapshot);
    bool hasSnapshot() const;
    TransactionSnapshot getLastSnapshot() const;
};

#endif
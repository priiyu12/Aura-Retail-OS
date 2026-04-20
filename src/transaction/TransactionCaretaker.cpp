#include "../../include/transaction/TransactionCaretaker.h"

void TransactionCaretaker::saveSnapshot(const TransactionSnapshot& snapshot) {
    snapshots.push_back(snapshot);
}

bool TransactionCaretaker::hasSnapshot() const {
    return !snapshots.empty();
}

TransactionSnapshot TransactionCaretaker::getLastSnapshot() const {
    return snapshots.back();
}
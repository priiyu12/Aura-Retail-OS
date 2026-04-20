#ifndef TRANSACTION_SNAPSHOT_H
#define TRANSACTION_SNAPSHOT_H

class TransactionSnapshot {
private:
    int productId;
    int stockBefore;
    int reservedBefore;

public:
    TransactionSnapshot(int productId, int stockBefore, int reservedBefore);

    int getProductId() const;
    int getStockBefore() const;
    int getReservedBefore() const;
};

#endif
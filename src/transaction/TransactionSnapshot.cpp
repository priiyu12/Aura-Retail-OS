#include "../../include/transaction/TransactionSnapshot.h"

TransactionSnapshot::TransactionSnapshot(int productId, int stockBefore, int reservedBefore)
    : productId(productId), stockBefore(stockBefore), reservedBefore(reservedBefore) {}

int TransactionSnapshot::getProductId() const { return productId; }
int TransactionSnapshot::getStockBefore() const { return stockBefore; }
int TransactionSnapshot::getReservedBefore() const { return reservedBefore; }
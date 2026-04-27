#include "../../include/models/Transaction.h"

Transaction::Transaction()
    : transactionId(0), type(""), productId(0), quantity(0),
      amount(0.0), paymentMethod(""), status("PENDING") {}

Transaction::Transaction(int transactionId,
                         const std::string& type,
                         int productId,
                         int quantity,
                         double amount,
                         const std::string& paymentMethod,
                         const std::string& status)
    : transactionId(transactionId),
      type(type),
      productId(productId),
      quantity(quantity),
      amount(amount),
      paymentMethod(paymentMethod),
      status(status) {}

int Transaction::getTransactionId() const { return transactionId; }
std::string Transaction::getType() const { return type; }
int Transaction::getProductId() const { return productId; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getPaymentMethod() const { return paymentMethod; }
std::string Transaction::getStatus() const { return status; }

void Transaction::setStatus(const std::string& status) {
    this->status = status;
}

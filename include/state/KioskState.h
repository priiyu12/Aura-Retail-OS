#ifndef KIOSK_STATE_H
#define KIOSK_STATE_H

#include <string>

class KioskState {
public:
    virtual bool canPurchase() const = 0;
    virtual bool canRestock() const = 0;
    virtual bool canRunDiagnostics() const = 0;
    virtual std::string getStateName() const = 0;
    virtual ~KioskState() = default;
};

#endif
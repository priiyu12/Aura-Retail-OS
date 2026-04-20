#ifndef FAILURE_HANDLER_H
#define FAILURE_HANDLER_H

#include <string>
#include <iostream>

class FailureHandler {
protected:
    FailureHandler* nextHandler;

public:
    FailureHandler() : nextHandler(nullptr) {}
    virtual ~FailureHandler() = default;

    void setNext(FailureHandler* next) {
        nextHandler = next;
    }

    virtual bool handle(const std::string& failureMessage) {
        if (nextHandler) return nextHandler->handle(failureMessage);
        return false;
    }
};

class RetryHandler : public FailureHandler {
public:
    bool handle(const std::string& failureMessage) override {
        std::cout << "[RECOVERY] RetryHandler processing: " << failureMessage << "\n";
        if (nextHandler) return nextHandler->handle(failureMessage);
        return false;
    }
};

class RecalibrationHandler : public FailureHandler {
public:
    bool handle(const std::string& failureMessage) override {
        std::cout << "[RECOVERY] RecalibrationHandler processing: " << failureMessage << "\n";
        if (nextHandler) return nextHandler->handle(failureMessage);
        return false;
    }
};

class TechnicianAlertHandler : public FailureHandler {
public:
    bool handle(const std::string& failureMessage) override {
        std::cout << "[RECOVERY] TechnicianAlertHandler processing: " << failureMessage << "\n";
        std::cout << "[RECOVERY] Technician has been notified.\n";
        return true;
    }
};

#endif
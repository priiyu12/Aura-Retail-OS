#ifndef HARDWARE_LAYER_H
#define HARDWARE_LAYER_H

class HardwareLayer {
private:
    bool failNextDispense;
    bool hardwareHealthy;

public:
    HardwareLayer();
    bool dispenseItem(int productId, int quantity);
    void runDiagnostics();
    void setFailNextDispense(bool fail);
    bool isHealthy() const;
};

#endif
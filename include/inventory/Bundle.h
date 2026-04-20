#ifndef BUNDLE_H
#define BUNDLE_H

#include <string>
#include <vector>

class Bundle {
private:
    int bundleId;
    std::string name;
    std::vector<int> productIds;
    std::vector<int> quantities;

public:
    Bundle();
    Bundle(int bundleId,
           const std::string& name,
           const std::vector<int>& productIds,
           const std::vector<int>& quantities);

    int getBundleId() const;
    std::string getName() const;
    std::vector<int> getProductIds() const;
    std::vector<int> getQuantities() const;
};

#endif
#ifndef DISCOUNT_SYSTEM_HPP
#define DISCOUNT_SYSTEM_HPP

#include <unordered_map>
#include <string>

using namespace std;
class DiscountSystem {
public:
    DiscountSystem(const string& filename);
    void addDiscount(int productId, double discount);
    double getDiscount(int productId) const;
    void saveToFileTsv(const string& filename) const;
    void readFromFile(const string& filename);
    const unordered_map<int, double>& getAllDiscounts() const;

private:
    unordered_map<int, double> discountList;
};

#endif // DISCOUNT_SYSTEM_HPP

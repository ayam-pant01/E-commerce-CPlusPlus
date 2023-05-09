#include "DiscountSystem.hpp"
#include <fstream>
#include <sstream>
#include <iostream>


DiscountSystem::DiscountSystem(const string& filename) {
    readFromFile(filename);
}

void DiscountSystem::addDiscount(int productId, double discount) {
    discountList[productId] = discount;
}

double DiscountSystem::getDiscount(int productId) const {
    auto it = discountList.find(productId);
    if (it != discountList.end()) {
        return it->second;
    }
    return 0;
}
const unordered_map<int, double>& DiscountSystem::getAllDiscounts() const {
    return discountList;
}


void DiscountSystem::saveToFileTsv(const string& filename) const {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {

        // write data rows
        for (const auto& entry : discountList) {
            outFile << entry.first << '\t' << entry.second << '\n';
        }

        outFile.close();
    }
    else {
        cerr << "Unable to open file: " << filename << '\n';
    }
}

void DiscountSystem::readFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Unable to open file " << filename << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string productIdStr, discountAmountStr;
        if (!(iss >> productIdStr >> discountAmountStr)) {
            cout << "Error reading line: " << line << endl;
            continue;
        }
        int productId = stoi(productIdStr);
        float discountAmount = stof(discountAmountStr);
        discountList[productId] = discountAmount;
    }
    inputFile.close();
}

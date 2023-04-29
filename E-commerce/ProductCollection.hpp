#ifndef PRODUCTCOLLECTION_HPP
#define PRODUCTCOLLECTION_HPP

#pragma once
#include "Product.hpp"
#include <iostream>

class ProductCollection {
private:
    struct Node {
        Product data;
        Node* left;
        Node* right;
        Node(const Product& data) : data(data), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int itemCount;

    Node* insert(Node* node, const Product& data);
    Node* find(Node* node, int id) const;
    Node* find(Node* node, const std::string& name) const;
    void printCollection(Node* node) const;
    void printCollectionToFile(Node* node, ofstream& writeFile) const;
    void printAllItemsToFile(ofstream& writeFile) const;
    void destroy(Node* node);

public:
    ProductCollection();
    ~ProductCollection();
    ProductCollection(const string& filename);
    void addItem(const Product& product);
//    void sortByCost();
//    void sortByName();
//    void sortByQuantity();
    Product* getItemById(int id) const;
    Product* getItemByName(const std::string& name) const;
    int getTotalItemCount() const;
    void printAllItems() const;
    void readProductFromFile(const string& filename);
    void saveProductToFile(const string& filename) const;
};


#endif //PRODUCTCOLLECTION_HPP

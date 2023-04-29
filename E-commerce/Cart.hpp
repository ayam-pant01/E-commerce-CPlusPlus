#ifndef CART_HPP
#define CART_HPP

#include "Product.hpp"

class Cart
{
public: // make Node public
    struct Node
    {
        Product data;
        Node* next;
        Node(const Product& data) : data(data), next(nullptr) {}
    };
private:
    Node* head;
    int itemCount;
    double totalCost;

public:
    Cart();
    ~Cart();
    void addItem(const Product& product);
    void removeItem(int id);
    void printCart() const;
    double getTotalCost() const;
    void clearCart();
    Node* getHeadNode()
    {
        return head;
    }
};

#endif // CART_HPP


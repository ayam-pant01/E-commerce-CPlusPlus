#ifndef ORDERCOLLECTION_HPP
#define ORDERCOLLECTION_HPP

#include "Order.hpp"

class OrderCollection {
private:
    struct Node {
        Order data;
        Node* next;
        Node* prev;
        Node(const Order& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int itemCount;
    int nextID;

    void addNodeToFront(const Order& order);
    void addNodeToEnd(const Order& order);

public:
    OrderCollection(const string& filename);
    ~OrderCollection();
    void addOrder(int userId, const Cart& cart, double totalCost, time_t timePlaced);
    void addExistingOrder(int id,int userId,const Cart& cart, double totalCost, time_t timePlaced);
    Order* getOrder(int id);
    Order* getLatestOrder(int userId);
    void removeOrder(int id);
    void printOrders() const;
    void saveOrderToFile(const string& filename) const;
    void readOrderFromFile(const string& filename);
    void printOrderCollection(bool isBoss,int userId);
};

#endif // ORDERCOLLECTION_HPP

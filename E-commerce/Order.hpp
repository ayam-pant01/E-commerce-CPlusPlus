#ifndef ORDER_HPP
#define ORDER_HPP

#include"Cart.hpp"
#include<string>
#include<ctime>

class Order
{
private:
    int id;
    int userId;
    Cart cart;
    double totalCost;
    time_t timePlaced;

public:
    Order(int id, int userId, const Cart& cart, double totalCost, time_t timePlaced);
    Order(int id, int userId, double totalCost, time_t timePlaced);
    int getID() const;
    int getUserId() const;
//    Cart getCart() const;
    Cart* getCart()
    {
        return &cart;
    }
    double getTotalCost() const;
    time_t getTimePlaced() const;
    void print() const;
};

#endif
// ORDER_HPP


#include "Order.hpp"
#include <iostream>

Order::Order(int id, int userId, const Cart& cart, double totalCost, time_t timePlaced)
    : id(id), userId(userId), cart(cart), totalCost(totalCost), timePlaced(timePlaced)
{

}

Order::Order(int id, int userId, double totalCost, time_t timePlaced) :
    id(id), userId(userId), totalCost(totalCost), timePlaced(timePlaced), cart()
{
}



int Order::getID() const
{
    return id;
}

int Order::getUserId() const
{
    return userId;
}

//Cart Order::getCart() const
//{
//    return cart;
//}

double Order::getTotalCost() const
{
    return totalCost;
}

time_t Order::getTimePlaced() const
{
    return timePlaced;
}

void Order::print() const
{
    char timeStr[80];
    struct tm timeInfo;
    localtime_s(&timeInfo, &timePlaced);
    strftime(timeStr, sizeof(timeStr), "%c", &timeInfo);

    cout << "Order #" << id << " for user #" << userId << endl;
    cout << "Total Cost: $" << totalCost << endl;
    cout << "Time Placed: " << timeStr << endl;
    cout << "Items in Cart: " << endl;
    cart.printCart();
}

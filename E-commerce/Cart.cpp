#include "Cart.hpp"
#include <iostream>

Cart::Cart()
{
    head = nullptr;
    itemCount = 0;
    totalCost = 0.0;
}

Cart::~Cart()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void Cart::addItem(const Product& product)
{
    Node* newNode = new Node(product);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    ++itemCount;
    totalCost += (product.getCost() * product.getQuantity());
}

void Cart::removeItem(int id)
{
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr && current->data.getID() != id)
    {
        prev = current;
        current = current->next;
    }
    if (current == nullptr)
    {
        return;
    }
    if (prev == nullptr)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }
    --itemCount;
    totalCost -= (current->data.getCost() * current->data.getQuantity());
    delete current;
}

void Cart::printCart() const
{
    cout << "Cart Contents:\n";
    cout << "==============\n";
    Node* current = head;
    while (current != nullptr)
    {
        current->data.print();
        cout << "\n";
        current = current->next;
    }
}

double Cart::getTotalCost() const
{
    return totalCost;
}

void Cart::clearCart()
{
    itemCount = 0;
    totalCost = 0.0;
    delete head;
    head = nullptr;
}

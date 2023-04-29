#include "Product.hpp"
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
// Initialize the static field for auto-incremented ID
int Product::nextId = 1;

// Constructor
Product::Product()
{
    this->id = nextId++;
    this->name = "";
    this->cost = 0.0;
    this->quantity = 0;
}
Product::Product(int id, string n, double c, int q)
{
    this->id = id;
    this->name = n;
    this->cost = c;
    this->quantity = q;
    if (id >= nextId) {
        nextId = id + 1;
    }
}

// Getters
int Product::getID() const
{
    return id;
}
string Product::getName() const
{
    return name;
}
double Product::getCost() const
{
    return cost;
}
int Product::getQuantity() const
{
    return quantity;
}

// Setters
void Product::setName(string n)
{
    name = n;
}
void Product::setCost(double p)
{
    cost = p;
}
void Product::setQuantity(int q)
{
    quantity = q;
}

int Product::read()
{
    cout << "Enter Product Information" << endl;
    cout << "Enter Product name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Enter Product cost: ";
    cin >> cost;
    cout << "Enter Product quantity: ";
    cin >> quantity;
    if(cin.good())
    {
        return 1;
    }
    else
    {
        string temp;
        cin.clear();
        getline(cin>>ws,temp);
        return 0;
    }
}

void Product::print() const
{
    stringstream stream;
    stream << fixed << setprecision(2) << cost;
    string costStr = stream.str();
    cout << id << "\t" << name << "\t" << costStr << "\t" << quantity << endl;
}

string Product::printStr() const
{
    stringstream stream;
    stream << fixed << setprecision(2) << cost;
    string costStr = stream.str();
    string printStr = to_string(id) + "\t" + name + "\t" + costStr + "\t" + to_string(quantity);
    cout << "Formatted string: " << printStr << endl; // add this line

    return printStr;
}

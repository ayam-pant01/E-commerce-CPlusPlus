#ifndef PRODUCT_HPP
#define PRODUCT_HPP


#include <iostream>
#include <string>
using namespace std;

class Product {
    private:
        static int nextId;
        int id;
        string name;
        double cost;
        int quantity;
    public:
        // Constructor
        Product();
        Product(int id, string n, double c,int q);

        // Getters
        int getID() const;
        string getName() const ;
        double getCost() const ;
        int getQuantity() const;

        // Setters
        void setName(string n) ;
        void setCost(double p);
        void setQuantity(int q);

        // Other methods
        int read();
        void print() const;
        string printStr() const;
};
#endif // PRODUCT_HPP

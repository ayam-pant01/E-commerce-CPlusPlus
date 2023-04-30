#ifndef WISHLIST_HPP
#define WISHLIST_HPP

#include "Product.hpp"
#include <set>

class Wishlist {
public:
    Wishlist();
    ~Wishlist();
    void addItem(Product item);
    void removeItem(Product item);
    bool contains(Product item);
    void printAllItems();
    void addToWishlist(Product item); 
    const Product* containsByName(string name);

private:
    set<Product> wishListProducts;
};
#endif // USER_HPP

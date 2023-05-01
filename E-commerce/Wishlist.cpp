#include "Wishlist.hpp"

//  // New For Phase 2 // Wishlist class that uses Set data structure//
Wishlist::Wishlist() {}

Wishlist::~Wishlist() {}

void Wishlist::addItem(Product product) {
    wishListProducts.insert(product);
}

void Wishlist::removeItem(Product product) {
    wishListProducts.erase(product);
}

bool Wishlist::contains(Product product) {
    return wishListProducts.count(product) > 0;
}

void Wishlist::printAllItems() {
    if (wishListProducts.size() > 0) {
        cout << "Items in Wishlist:\n";
        cout << "Name\tCost\n";
        for (const auto& product : wishListProducts) {

            cout << product.getName() << "\t$" << product.getCost() << "\n";
        }
    }
    else {
        cout << "No items found in wishlist.\n";
    }
}

void Wishlist::addToWishlist(Product product) {
    if (!contains(product)) {
        addItem(product);
        cout << product.getName() << " added to wishlist!\n";
    }
    else {
        cout << product.getName() << " is already in your wishlist.\n";
    }
}

const Product* Wishlist::containsByName(string name) {
    for (auto& product : wishListProducts) {
        if (product.getName() == name) {
            return &product;
        }
    }
    return nullptr;
}

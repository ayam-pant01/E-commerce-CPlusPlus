#include <iostream>

#include "ProductCollection.hpp"
#include "UserCollection.hpp"
#include "OrderCollection.hpp"
#include "User.hpp"
#include "Cart.hpp"
#include "Order.hpp"

#define PRODUCT_FILE "Product List.txt"
#define USER_FILE "User List.txt"
#define ORDER_FILE "Order List.txt"

using namespace std;
void printEcommerceFeatures();
void showMenu();
void login();
void addProducts();
void addUsers();
void addToCart();
void displayCart();
void checkOutMenu();
void processPayment();
void processOrder();
void viewOrder(bool isBoss, int userId);

void userManagement();
void productManagement();
User* currentUser;
UserCollection userCol(USER_FILE);
ProductCollection prodCol(PRODUCT_FILE);
Cart* cart;
OrderCollection currentOrderList(ORDER_FILE);

int main()
{
    cout<< "Welcome to my first e-commerce app!\n" << endl;
    printEcommerceFeatures();
    showMenu();
    return 0;
}


void printEcommerceFeatures()
{
    cout << "\tHere are 5 basic features that is implemented for this e-commerce app: " << endl;
    cout << "\t1. User Authentication: Users should be able to register and login to the application to access its features." << endl;
    cout << "\t2. Product Catalog Management: There should be a catalog of products available for users to browse and search." << endl;
    cout << "\t3. Shopping Cart Management: Users should be able to add products to a cart and view the contents of the cart." << endl;
    cout << "\t4. Order Processing: Users should be able to place orders and track their order status." << endl;
    cout << "\t5. Payment Processing: Users should be able to securely pay for their orders using a payment gateway." << endl;
}


void showMenu()
{
    int choice;
    do
    {
        cout << "\nWhat would you like to do?\n";
        int loggedInUserId = (currentUser != nullptr) ? currentUser->getID() : -1;
        //loggedInUserId = 0; // remove this code later.
        if (loggedInUserId == 0)
        {
            cout << "1. User management\n";
            cout << "2. Product management\n";
            cout << "3. View Orders\n";
            cout << "4. Login as different user\n";
            cout << "0. Exit program\n";
            cout << "Enter your choice (0-4): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                // User management
                userManagement();
                break;
            case 2:
                // Product management
                productManagement();
                break;
            case 3:
                // Product management
                cout << "\nDisplaying orders for logged in user....\n";
                viewOrder(1,loggedInUserId);
                break;
            case 4:
                // Product management
                login();
                break;
            case 0:
                cout << "\nExiting...\n";
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
        else if (loggedInUserId > 0)
        {
            cout << "1. Start Shopping\n";
            cout << "2. View Orders\n";
            cout << "0. Exit program\n";
            cout << "Enter your choice (0-2): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                productManagement();
                break;
            case 2:
                cout << "\nDisplaying orders for logged in user....\n";
                viewOrder(0,loggedInUserId);
                break;
            case 0:
                cout << "\nExiting...\n";
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
            }

        }
        else
        {
            cout << "1. Log in\n";
            cout << "2. Create new user\n";
            cout << "0. Exit program\n";
            cout << "Enter your choice (0-2): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                // Log in
                login();
                break;
            }
            case 2:
            {
                // Log in
                addUsers();
                break;
            }
            case 0:
                cout << "\nExiting...\n";
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
    }
    while (choice != 0);
}

void login()
{
    string uname;
    cout << "Enter username: ";
    getline(cin>>ws,uname);
    User* user = userCol.getUserByUsername(uname);
    if (user != nullptr)
    {
        string password;
        cout << "Enter password: ";
        cin >> password;
        if (user->getPassword() == password)
        {
            currentUser = user;
            cout << "\nLogged in as " << user->getName() << ".\n";
            cart = new Cart();
        }
        else
        {
            cout << "\nIncorrect password.\n";
        }
    }
    else
    {
        cout << "\nUser not found.\n";
    }
}

void addProducts()
{
    int numProducts;
    cout << "How many products would you like to add? ";
    cin >> numProducts;

    for (int i = 0; i < numProducts; i++)
    {
        cout << "Product #" << i + 1 << ":" << endl;
        Product product;
        if(product.read())
        {
            prodCol.addItem(product);
            prodCol.saveProductToFile(PRODUCT_FILE);
        }
    }
}

void addUsers()
{
    User newUser;
    if(newUser.read())
    {
        userCol.add(newUser);
        cout << "\nUser: " <<newUser.getName() << " successfully added!\n" << endl;
        userCol.saveUsersToFile(USER_FILE);
    }
}

void addToCart()
{
    string name;
    int quantity;

    cout << "\nEnter the name of the item to add to cart: ";
    cin >> name;

    // Find the product in the collection
    Product* cartItem = prodCol.getItemByName(name);
    if (cartItem == NULL)
    {
        cout << "\nProduct not found.\n";
        return;
    }

    // Get the quantity of the product to add to cart
    cout << "Enter the quantity of " << cartItem->getName() << " to add to cart: ";
    cin >> quantity;

    // Check if the quantity is valid
    if (quantity <= 0)
    {
        cout << "\nInvalid quantity. Please try again.\n";
        return;
    }
    else if (quantity > cartItem->getQuantity())
    {
        cout << "\nNot enough stock. Only " << cartItem->getQuantity() << " available.\n";
        return;
    }
    Product itemRef = *cartItem;
    itemRef.setQuantity(quantity);
    // Add the product to the user's cart
    cart->addItem(itemRef);
    cout << "\n" << quantity << " " << cartItem->getName() << " added to cart.\n";
}

void displayCart()
{
    cout << "\nYour Cart:\n";
    cart->printCart();
    cout << "Total cost: $" << cart->getTotalCost() << endl;
}

void userManagement()
{
    if (currentUser->getUsername() == "boss")
    {
        int choice;
        do
        {
            cout << "\nWhat would you like to do?\n";
            cout << "1. List users\n";
            cout << "2. Add user\n";
            cout << "0. Exit user management\n";
            cout << "Enter your choice (0-2): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "\nList of Users:\n";
                userCol.printAllItems();
                break;
            case 2:
                addUsers();
                break;
            case 0:
                cout << "\nExiting user management...\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
        while (choice != 0);
    }
    else
    {
        cout << "\nYour user info:\n";
        //users.printItemById(userId); // assuming a method to print a single user by id
    }
}

void productManagement()
{
    int choice;
    bool isBoss = (currentUser->getUsername() == "boss");

    do
    {
        cout << "\nWhat would you like to do?\n";
        cout << "1. List products\n";
        if (isBoss)
        {
            cout << "2. Add product\n";
            cout << "3. Search product\n";
            cout << "4. Sort products by name\n";
            cout << "5. Sort products by cost\n";
            cout << "0. Exit product management\n";
            cout << "Enter your choice (1-5): ";
        }
        else
        {
            cout << "2. Add to cart\n";
            cout << "3. Search product\n";
            cout << "4. Sort products by name\n";
            cout << "5. Sort products by cost\n";
            cout << "6. View cart\n";
            cout << "7. Checkout\n";
            cout << "0. Exit product management\n";
            cout << "Enter your choice (0-7): ";
        }
        cin >> choice;
        if(isBoss && choice > 5)
            choice = -1;

        switch (choice)
        {
        case 1:
            cout << "\nList of Products:\n";
            prodCol.printAllItems();
            break;
        case 2:
            if (isBoss)
            {
                addProducts();
            }
            else
            {
                addToCart();
            }
            break;
        case 3:
        {
            string name;
            cout << "\nEnter the name of the product to search: ";
            getline(cin>>ws,name);
            Product* result = prodCol.getItemByName(name);
            if (result != nullptr)
            {
                cout << "\nProduct found:\n";
                cout << "Id.\tName\tCost\tQuantity" << endl;
                result->print();
            }
            else
            {
                cout << "\nProduct not found.\n";
            }
            break;
        }
        case 4:
            // sortByName();
            cout << "\nProducts sorted by name.\n";
            break;
        case 5:
            //sortByCost();
            cout << "\nProducts sorted by cost.\n";
            break;
        case 6:
            cout << "\nProceeding to cart...\n";
            displayCart();
            break;
        case 7:
            cout << "\Checkout Menu...\n";
            displayCart();
            checkOutMenu();
            break;
        case 0:
            cout << "\nExiting product management...\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while (choice != 0);
}

void checkOutMenu()
{
    int choice;
    do
    {
        cout << "Do you like to confirm your order?\n";
        cout << "1. Confirm item list and proceed to payment.\n";
        cout << "0. Exit checkout.\n";
        cout << "Enter your choice (0-1): ";
        cin >> choice;
        switch(choice)
        {
        case 1:
            processPayment();
            break;
        case 0:
            cout << "Exiting checkout...\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while (choice < 0 && choice > 1);
}

void processPayment()
{
    int paymentChoice;
    do
    {
        cout << "Proceeding to payment...\n";
        cout << "Choose payment option.\n";
        cout << "1. Cash.\n";
        cout << "2. Card.\n";
        cout << "0. Cancel Payment\n";
        cin >> paymentChoice;

        switch(paymentChoice)
        {
        case 1:
            cout << "Cash Payment option confirmed. Your items will be delivered in 7 business days.\n";
            cout << "Please pay the cash on delivery.\n";
            processOrder();
            break;
        case 2:
            cout << "Card Payment option confirmed. Your items will be delivered in 7 business days.\n";
            cout << "Please swipe your card on delivery.\n";
            processOrder();
            break;
        case 0:
            cout << "Canceling payment...\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }
    while(paymentChoice < 0 && paymentChoice > 2);
}

void processOrder()
{
    currentOrderList.addOrder(currentUser->getID(),*cart,cart->getTotalCost(),time(0));
   //currentOrderList.printOrderCollection(0,currentUser->getID());
    //currentOrderList.saveOrderToFile(ORDER_FILE);
    cart = new Cart();
//// Save order list.
//// order class should have user id, and cart list.
}

void viewOrder(bool isBoss, int userId)
{
    currentOrderList.printOrderCollection(isBoss,userId);
}





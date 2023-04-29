#include "ProductCollection.hpp"
#include <algorithm>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>


ProductCollection::ProductCollection() : root(nullptr), itemCount(0) {}

ProductCollection::~ProductCollection()
{
    destroy(root);
}
ProductCollection::ProductCollection(const string& filename)
{
    readProductFromFile(filename);
}

void ProductCollection::addItem(const Product& product)
{
    root = insert(root, product);
    itemCount++;
}

ProductCollection::Node* ProductCollection::insert(Node* node, const Product& data)
{
    if (node == nullptr)
    {
        return new Node(data);
    }

    if (data.getName() < node->data.getName())
    {
        node->left = insert(node->left, data);
    }
    else
    {
        node->right = insert(node->right, data);
    }

    return node;
}

void ProductCollection::destroy(Node* node)
{
    if (node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

Product* ProductCollection::getItemById(int id) const
{
    Node* node = find(root, id);
    if (node == nullptr)
    {
        return nullptr;
    }
    return &node->data;
}

ProductCollection::Node* ProductCollection::find(Node* node, int id) const
{
    if (node == nullptr || node->data.getID() == id)
    {
        return node;
    }
    else if (id < node->data.getID())
    {
        return find(node->left, id);
    }
    else
    {
        return find(node->right, id);
    }
}

Product* ProductCollection::getItemByName(const string& name) const
{
    Node* node = find(root, name);
    if (node)
    {
        return &(node->data);
    }
    else
    {
        return nullptr;
    }
}


// Private method to recursively find a node in the binary search tree by product name
ProductCollection::Node* ProductCollection::find(Node* node, const string& name) const
{
    if (node == nullptr || node->data.getName() == name)
    {
        return node;
    }
    else if (name < node->data.getName())
    {
        return find(node->left, name);
    }
    else
    {
        return find(node->right, name);
    }
}
//
//void ProductCollection::sortByCost() {
//    // Implementing merge sort algorithm
//    root = mergeSort(root, [](const Product& a, const Product& b) {
//        return a.getCost() < b.getCost();
//    });
//}
//
//void ProductCollection::sortByName() {
//    // Implementing merge sort algorithm
//    root = mergeSort(root, [](const Product& a, const Product& b) {
//        return a.getName() < b.getName();
//    });
//}
//
//void ProductCollection::sortByQuantity() {
//    // Implementing merge sort algorithm
//    root = mergeSort(root, [](const Product& a, const Product& b) {
//        return a.getQuantity() < b.getQuantity();
//    });
//}

int ProductCollection::getTotalItemCount() const
{
    return itemCount;
}


void ProductCollection::printAllItems() const
{
    cout << "Id.\tName\tCost\tQuantity" << endl;
    printCollection(root);
}

void ProductCollection::printCollection(Node* node) const
{
    if (node != nullptr)
    {
        printCollection(node->left);
        node->data.print();
        printCollection(node->right);
    }
    else if(root == nullptr)
    {
        cout << "No product found!! Please add products to the list." <<endl;
    }
}

void ProductCollection::printAllItemsToFile(ofstream& writeFile) const
{
    printCollectionToFile(root,writeFile);
}

void ProductCollection::printCollectionToFile(Node* node, ofstream& writeFile) const
{
    if (node != nullptr)
    {
        printCollectionToFile(node->left, writeFile);
        writeFile << node->data.printStr() << endl;
        printCollectionToFile(node->right, writeFile);
    }
    else if (root == nullptr)
    {
        cout << "No product found!! Please add products to the list." << endl;
    }
}


void ProductCollection::readProductFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string id_str, name, cost_str, quantity_str;
            if (getline(iss, id_str, '\t') &&
                    getline(iss >> ws, name, '\t') &&
                    getline(iss >> ws, cost_str, '\t') &&
                    getline(iss >> ws, quantity_str, '\t'))
            {

                try
                {
                    int id = stoi(id_str);
                    double cost = stod(cost_str);
                    int quantity = stoi(quantity_str);
                    Product product(id, name, cost, quantity);
                    addItem(product);
                }
                catch (const exception& e)
                {
                    // Error parsing product data from file
                    cerr << "Error reading product from file: " << e.what() << endl;
                }
            }
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void ProductCollection::saveProductToFile(const string& filename) const
{
    ofstream writeFile(filename);

    if (!writeFile)
    {
        cerr << "Error: unable to open writeFile!" << endl;
        return;
    }

    this->printAllItemsToFile(writeFile);
    writeFile.close();
    cout << "Product list saved to file!" << endl;
}


//void ProductCollection::inorderTraversal(Node* node, vector<Product>& productList) const {
//    if (node == nullptr) {
//        return;
//    }
//
//    inorderTraversal(node->left, productList);
//    productList.push_back(node->data);
//    inorderTraversal(node->right, productList);
//}

//
//ProductCollection::Node* ProductCollection::mergeSort(Node* head, function<bool(const Product&, const Product&)> comp) {
//    if (head == nullptr || head->right == nullptr) {
//        return head;
//    }
//
//    Node* mid = getMiddle(head);
//    Node* left = mergeSort(head, comp);
//    Node* right = mergeSort(mid, comp);
//
//    return merge(left, right, comp);
//}
//
//ProductCollection::Node* ProductCollection::getMiddle(Node* head) {
//    Node* slow = head;
//    Node* fast = head->right;
//
//    while (fast != nullptr) {
//        fast = fast->right;
//        if (fast != nullptr) {
//            slow = slow->right;
//            fast = fast->right;
//        }
//    }
//
//    Node* mid = slow->right;
//    slow->right = nullptr;
//
//    return mid;
//}
//
//ProductCollection::Node* ProductCollection::merge(Node* left, Node* right, function<bool(const Product&, const Product&)> comp) {
//    Node* result = nullptr;
//
//    if (left == nullptr) {
//        return right;
//    }
//    if (right == nullptr) {
//        return left;
//    }
//
//    if (comp(left->data, right->data)) {
//        result = left;
//        result->right = merge(left->right, right, comp);
//    } else {
//        result = right;
//        result->right = merge(left, right->right, comp);
//    }
//
//    return result;
//}
//

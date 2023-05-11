#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include <ctime>

enum class Color { RED, BLACK };
using namespace std;
struct OrderNode {
    int orderId;
    int userId;
    double cost;
    time_t timePlaced;
    OrderNode* parent;
    OrderNode* left;
    OrderNode* right;
    Color color;

    OrderNode(int orderId, int userId, double cost, time_t timePlaced) {
        this->orderId = orderId;
        this->userId = userId;
        this->cost = cost;
        this->timePlaced = timePlaced;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->color = Color::RED;
    }
};

class OrderHistory {
private:
    OrderNode* root;

    void rotateLeft(OrderNode* x);
    void rotateRight(OrderNode* x);
    void fixInsertion(OrderNode* x);
    void fixDeletion(OrderNode* x);
    void transplant(OrderNode* u, OrderNode* v);
    OrderNode* minimum(OrderNode* node);
    bool inorderTraversal(OrderNode* node, bool isBoss, int userId) const;
    void destroySubtree(OrderNode* node);
    void saveHelper(const OrderNode* node, ofstream& outfile) const;

public:
    OrderHistory(const string& filename);
    ~OrderHistory();

    void insert(int orderId, int userId, double cost, time_t timePlaced);
    OrderNode* search(time_t orderDate);
    void remove(OrderNode* order);
    void printByUserId(bool isBoss, int userId) const;
    void saveOrderHistoryToFile(const string& filename) const;
    void loadOrderHistoryFromFile(const string& filename);
};

#endif

#define _XOPEN_SOURCE
#include <ctime>
#include "OrderHistory.hpp"
#include <fstream>
#include <sstream>

OrderHistory::OrderHistory(const string& filename) {
	root = nullptr;
	loadOrderHistoryFromFile(filename);
}

OrderHistory::~OrderHistory() {
	destroySubtree(root);
}

void OrderHistory::destroySubtree(OrderNode* node) {
	if (node == nullptr) {
		return;
	}

	destroySubtree(node->left);
	destroySubtree(node->right);
	delete node;
}



void OrderHistory::insert(int orderId, int userId, double cost, time_t timePlaced) {
	// Create a new node with the given data
	OrderNode* newNode = new OrderNode(orderId, userId, cost, timePlaced);

	// Case 1: Tree is empty, make the new node the root
	if (root == nullptr) {
		root = newNode;
		newNode->color = Color::BLACK;
		return;
	}

	// Traverse the tree to find the correct position for the new node
	OrderNode* current = root;
	OrderNode* parent = nullptr;
	while (current != nullptr) {
		parent = current;
		if (timePlaced < current->timePlaced) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	// Insert the new node as a child of the parent
	newNode->parent = parent;
	if (timePlaced < parent->timePlaced) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	// Fix any violations of the Red-Black Tree properties that may have occurred during insertion
	fixInsertion(newNode);
}

OrderNode* OrderHistory::search(time_t orderDate) {
	// Traverse the tree until the node with the given order date is found
	OrderNode* current = root;
	while (current != nullptr && current->timePlaced != orderDate) {
		if (orderDate < current->timePlaced) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	// Return the data in the node, or nullptr if the node wasn't found
	if (current != nullptr) {
		return current;
	}
	else {
		return nullptr;
	}
}

void OrderHistory::remove(OrderNode* order) {
	if (order == nullptr) {
		return;
	}

	OrderNode* x;
	OrderNode* y = order;
	Color yOriginalColor = y->color;

	if (order->left == nullptr) {
		x = order->right;
		transplant(order, order->right);
	}
	else if (order->right == nullptr) {
		x = order->left;
		transplant(order, order->left);
	}
	else {
		y = minimum(order->right);
		yOriginalColor = y->color;
		x = y->right;
		if (y->parent == order) {
			x->parent = y;
		}
		else {
			transplant(y, y->right);
			y->right = order->right;
			y->right->parent = y;
		}
		transplant(order, y);
		y->left = order->left;
		y->left->parent = y;
		y->color = order->color;
	}

	if (yOriginalColor == Color::BLACK) {
		fixDeletion(x);
	}

	delete order;
}

void OrderHistory::transplant(OrderNode* u, OrderNode* v) {
	if (!u->parent) {
		root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

OrderNode* OrderHistory::minimum(OrderNode* node) {
	OrderNode* current = node;
	while (current->left != nullptr) {
		current = current->left;
	}
	return current;
}



void OrderHistory::fixInsertion(OrderNode* x) {
	while (x != root && x->parent->color == Color::RED) {
		if (x->parent == x->parent->parent->left) {
			OrderNode* y = x->parent->parent->right;
			if (y && y->color == Color::RED) {
				x->parent->color = Color::BLACK;
				y->color = Color::BLACK;
				x->parent->parent->color = Color::RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					rotateLeft(x);
				}
				x->parent->color = Color::BLACK;
				x->parent->parent->color = Color::RED;
				rotateRight(x->parent->parent);
			}
		}
		else {
			OrderNode* y = x->parent->parent->left;
			if (y && y->color == Color::RED) {
				x->parent->color = Color::BLACK;
				y->color = Color::BLACK;
				x->parent->parent->color = Color::RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					rotateRight(x);
				}
				x->parent->color = Color::BLACK;
				x->parent->parent->color = Color::RED;
				rotateLeft(x->parent->parent);
			}
		}
	}
	root->color = Color::BLACK;
}

void OrderHistory::fixDeletion(OrderNode* x) {
	while (x != root && x->color == Color::BLACK) {
		if (x == x->parent->left) {
			OrderNode* w = x->parent->right;
			if (w->color == Color::RED) {
				w->color = Color::BLACK;
				x->parent->color = Color::RED;
				rotateLeft(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == Color::BLACK && w->right->color == Color::BLACK) {
				w->color = Color::RED;
				x = x->parent;
			}
			else {
				if (w->right->color == Color::BLACK) {
					w->left->color = Color::BLACK;
					w->color = Color::RED;
					rotateRight(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = Color::BLACK;
				w->right->color = Color::BLACK;
				rotateLeft(x->parent);
				x = root;
			}
		}
		else {
			OrderNode* w = x->parent->left;
			if (w->color == Color::RED) {
				w->color = Color::BLACK;
				x->parent->color = Color::RED;
				rotateRight(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == Color::BLACK && w->left->color == Color::BLACK) {
				w->color = Color::RED;
				x = x->parent;
			}
			else {
				if (w->left->color == Color::BLACK) {
					w->right->color = Color::BLACK;
					w->color = Color::RED;
					rotateLeft(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = Color::BLACK;
				w->left->color = Color::BLACK;
				rotateRight(x->parent);
				x = root;
			}
		}
	}
	x->color = Color::BLACK;
}


void OrderHistory::rotateLeft(OrderNode* x) {
	// Make y the right child of x
	OrderNode* y = x->right;
	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void OrderHistory::rotateRight(OrderNode* x) {
	// Make y the left child of x
	OrderNode* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}


void OrderHistory::printByUserId(bool isBoss, int userId) const {
	if (root != nullptr) {
		bool ordersFound = inorderTraversal(root, isBoss, userId);
		if (!ordersFound) {
			cout << "No order found!" << endl;
		}
		return;
	}
	else {
		// No order found with the given userId
		cout << "No order found!" << endl;
	}
}

// Helper function for inorder traversal
bool OrderHistory::inorderTraversal(OrderNode* node, bool isBoss, int userId) const {
	if (node == nullptr) {
		return false;
	}

	bool ordersFound = false;
	ordersFound = inorderTraversal(node->left, isBoss, userId) || ordersFound;
	if (isBoss || (node->userId == userId && !isBoss)) {
		cout << "\nOrder ID: " << node->orderId << endl;
		cout << "User ID: " << node->userId << endl;
		cout << "Total: $" << node->cost << endl;
		char buffer[26];
		ctime_s(buffer, sizeof buffer, &(node->timePlaced));
		cout << "Time placed: " << buffer << "\n";
		ordersFound = true;
	}
	ordersFound = inorderTraversal(node->right, isBoss, userId) || ordersFound;

	return ordersFound;
}

void OrderHistory::saveOrderHistoryToFile(const string& filename) const {
	ofstream outfile(filename);
	if (!outfile) {
		cerr << "Error: could not open file \"" << filename << "\"" << endl;
		return;
	}
	saveHelper(root, outfile);
	outfile.close();
}

void OrderHistory::saveHelper(const OrderNode* node, ofstream& outfile) const {
	if (node == nullptr) {
		return;
	}
	saveHelper(node->left, outfile);
	outfile << node->orderId << "\t" << node->userId << "\t" << node->cost << "\t" << node->timePlaced << "\n";
	saveHelper(node->right, outfile);
}

void OrderHistory::loadOrderHistoryFromFile(const string& filename) {
	ifstream infile(filename);
	if (!infile) {
		cerr << "Error: could not open file \"" << filename << "\"" << endl;
		return;
	}

	// Clear the existing order history
	//clear();

	// Read orders from the file
	int orderId, userId;
	double cost;
	time_t timePlaced;
	while (infile >> orderId >> userId >> cost >> timePlaced) {
		insert(orderId, userId, cost, timePlaced);
	}

	infile.close();
}



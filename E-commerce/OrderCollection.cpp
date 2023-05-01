#include "OrderCollection.hpp"
#include <fstream>
#include <sstream>

OrderCollection::OrderCollection(const string& filename)
{
	head = nullptr;
	tail = nullptr;
	itemCount = 0;
	nextID = 1;
	readOrderFromFile(filename);
}

OrderCollection::~OrderCollection()
{
	Node* current = head;
	while (current != nullptr)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
}

void OrderCollection::addNodeToFront(const Order& order)
{
	Node* newNode = new Node(order);
	newNode->next = head;
	if (head != nullptr)
	{
		head->prev = newNode;
	}
	head = newNode;
	++itemCount;
}

void OrderCollection::addNodeToEnd(const Order& order)
{
	Node* newNode = new Node(order);
	if (tail == nullptr) // if the list is empty
	{
		head = tail = newNode;
	}
	else
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	++itemCount;
}

void OrderCollection::addOrder(int userId, const Cart& cart, double totalCost, time_t timePlaced)
{
	int id = nextID;
	Order order(id, userId, cart, totalCost, timePlaced);

	if (head == nullptr)
	{
		// If the linked list is empty, add the new node to the front
		addNodeToFront(order);
		tail = head;
	}
	else if (order.getTimePlaced() >= head->data.getTimePlaced())
	{
		// If the new node has a later timestamp than the head node, add it to the front
		addNodeToFront(order);
	}
	else if (order.getTimePlaced() <= tail->data.getTimePlaced())
	{
		// If the new node has an earlier timestamp than the tail node, add it to the end
		addNodeToEnd(order);
		tail = tail->next; // Update the tail pointer to point to the new node
	}
	else
	{
		// Otherwise, insert the new node in the correct order in the middle of the linked list
		Node* current = head;
		while (current->next != nullptr && current->next->data.getTimePlaced() >= order.getTimePlaced())
		{
			current = current->next;
		}
		Node* newNode = new Node(order);
		newNode->next = current->next;
		if (current->next != nullptr)
		{
			current->next->prev = newNode;
		}
		current->next = newNode;
		newNode->prev = current;
		++itemCount;
	}
}


//void OrderCollection::addOrder(int userId, const Cart& cart, double totalCost, time_t timePlaced)
//{
//    int id = nextID;
//    Order order(id, userId, cart, totalCost, timePlaced);
//    if (head == nullptr)
//    {
//        addNodeToFront(order);
//        tail = head;
//    }
//    else if (order.getTimePlaced() >= head->data.getTimePlaced())
//    {
//        addNodeToFront(order);
//    }
//    else if (order.getTimePlaced() <= tail->data.getTimePlaced())
//    {
//        addNodeToEnd(order);
//    }
//    else
//    {
//        Node* current = head;
//        while (current->next != nullptr && current->next->data.getTimePlaced() >= order.getTimePlaced())
//        {
//            current = current->next;
//        }
//        Node* newNode = new Node(order);
//        newNode->next = current->next;
//        current->next->prev = newNode;
//        current->next = newNode;
//        newNode->prev = current;
//        ++itemCount;
//        delete newNode;
//    }
//    Cart::Node* cartNode = order.getCart()->getHeadNode(); // get head node of cart linked list
//    Node* current = head;
//    cout << "Item Detail :" << endl;
//    cout <<"\tId\tName\tCost\tQuantity" << endl;
//    while (cartNode != nullptr)
//    {
//
//        cout << "\t" << cartNode->data.printStr() << endl;
//        cartNode = cartNode->next;
//    }
//    delete cartNode;
//
//    ++nextID;
//}

void OrderCollection::addExistingOrder(int id, int userId, const Cart& cart, double totalCost, time_t timePlaced)
{
	Order order(id, userId, cart, totalCost, timePlaced);
	if (head == nullptr)
	{
		addNodeToFront(order);
		tail = head;
	}
	else if (order.getTimePlaced() >= head->data.getTimePlaced())
	{
		addNodeToFront(order);
	}
	else if (order.getTimePlaced() <= tail->data.getTimePlaced())
	{
		addNodeToEnd(order);
	}
	else
	{
		Node* current = head;
		while (current->next != nullptr && current->next->data.getTimePlaced() >= order.getTimePlaced())
		{
			current = current->next;
		}
		Node* newNode = new Node(order);
		newNode->next = current->next;
		current->next->prev = newNode;
		current->next = newNode;
		newNode->prev = current;
		++itemCount;
		delete newNode;
	}

	++nextID;
}



Order* OrderCollection::getOrder(int id)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data.getID() == id)
		{
			return &(current->data);
		}
		current = current->next;
	}
	return nullptr;
}

Order* OrderCollection::getLatestOrder(int userId)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data.getUserId() == userId)
		{
			return &(current->data);
		}
		current = current->next;
	}
	return nullptr;
}

void OrderCollection::removeOrder(int id)
{
	Node* current = head;
	while (current != nullptr && current->data.getID() != id)
	{
		current = current->next;
	}
	if (current == nullptr)
	{
		return;
	}
	if (current == head)
	{
		head = current->next;
		if (head != nullptr)
		{
			head->prev = nullptr;
		}
		else
		{
			tail = nullptr;
		}
	}
	else if (current == tail)
	{
		tail = current->prev;
		tail->next = nullptr;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	delete current;
}

void OrderCollection::printOrders() const
{
	//cout << "Order List (" << size << " orders)\n";
	Node* current = head;
	while (current != nullptr)
	{
		current->data.print();
		current = current->next;
	}
}

void OrderCollection::saveOrderToFile(const string& filename) const
{
	ofstream outfile(filename);

	if (!outfile)
	{
		cerr << "Error: could not open file " << filename << endl;
		return;
	}

	for (Node* curr = head; curr != nullptr; curr = curr->next)
	{
		// Write cart item details with "C" prefix
		Cart* cart = curr->data.getCart();
		Cart::Node* cartNode = cart->getHeadNode(); // get head node of cart linked list
		while (cartNode != nullptr)
		{

			outfile << "C\t" << cartNode->data.printStr() << endl;
			cartNode = cartNode->next;
		}
		// Write order details with "O" prefix
		outfile << "O\t" << curr->data.getID() << '\t' << curr->data.getUserId() << '\t' << curr->data.getTotalCost() << '\t' << curr->data.getTimePlaced() << endl;
	}

	cout << "Orders saved to file " << filename << endl;
	outfile.close();
}

void OrderCollection::printOrderCollection(bool isBoss, int userId)
{
	for (Node* curr = head; curr != nullptr; curr = curr->next)
	{
		if (isBoss)
		{
			// Write order details with "O" prefix
			cout << "\nOrder Detail :" << endl;
			cout << "Id\tUser\tTotal\tOrderTime" << endl;
			cout << curr->data.getID() << '\t' << curr->data.getUserId() << '\t' << curr->data.getTotalCost() << '\t' << curr->data.getTimePlaced() << endl;
			// Write cart item details with "C" prefix
			Cart* cart = curr->data.getCart();
			Cart::Node* cartNode = cart->getHeadNode(); // get head node of cart linked list

			cout << "Item Detail :" << endl;
			cout << "\tId\tName\tCost\tQuantity" << endl;
			while (cartNode != nullptr)
			{

				cout << "\t" << cartNode->data.printStr() << endl;
				cartNode = cartNode->next;
			}

		}
		else
		{
			if (curr->data.getUserId() == userId)
			{
				cout << "\nOrder Detail :" << endl;
				cout << "Id\tUser\tTotal\tOrderTime" << endl;
				cout << curr->data.getID() << '\t' << curr->data.getUserId() << '\t' << curr->data.getTotalCost() << '\t' << curr->data.getTimePlaced() << endl;
				// Write cart item details with "C"

				cout << "----222-----" << endl;
				Cart* cart = curr->data.getCart();
				Cart::Node* cartNode = cart->getHeadNode();

				cout << "Item Detail :" << endl;
				cout << "\tId\tName\tCost\tQuantity" << endl;
				while (cartNode != nullptr)
				{
					cout << "\t" << cartNode->data.printStr() << endl;
					cartNode = cartNode->next;
				}
			}
			else
			{
				cout << "No order found for current user.\n";
			}
		}
	}
}

void OrderCollection::readOrderFromFile(const string& filename)
{
	ifstream infile(filename);

	if (!infile)
	{
		cerr << "Error: could not open file " << filename << endl;
		return;
	}
	Cart* cart = new Cart();
	string line;
	while (getline(infile, line))
	{
		istringstream iss(line);
		string prefix;
		iss >> prefix;

		if (prefix == "C")
		{
			int id, quantity;
			string name;
			double cost;
			iss >> id >> name >> cost >> quantity;
			Product product(id, name, cost, quantity);
			cart->addItem(product);
		}
		else if (prefix == "O")
		{
			int id, userId;
			double totalCost;
			time_t timePlaced;
			iss >> id >> userId >> totalCost >> timePlaced;
			addExistingOrder(id, userId, *cart, totalCost, time(0));
			cart = new Cart();

		}
		else
		{
			cerr << "Error: invalid prefix " << prefix << endl;
		}
	}

	infile.close();
}

#include "User.hpp"
#include <string>
#include <iostream>
// Initialize the static field for auto-incremented ID
int User::nextId = 1;

// Constructor
User::User()
{
    this->name = "";
    this->username = "";
    this->password = "";
    this->email = "";
    this->id = nextId++;
}
User::User(int id,string n,string u,string e, string p)
{
    this->id = id;
    this->name = n;
    this->username = u;
    this->email = e;
    this->password = p;
    if (id >= nextId)
    {
        nextId = id + 1;
    }
}

// Getters
int User::getID()
{
    return id;
}
string User::getName()
{
    return name;
}
string User::getUsername()
{
    return username;
}
string User::getPassword()
{
    return password;
}
string User::getEmail()
{
    return email;
}

// Setters
void User::setName(string n)
{
    name = n;
}
void User::setUsername(string u)
{
    username = u;
}
void User::setPassword(string p)
{
    password = p;
}
void User::setId(int i)
{
    id = i;
}
void User::setEmail(string e)
{
    email = e;
}

// Method to register a user
void User::registerUser()
{
    // Code to add user information to database or file
    cout << "User " << username << " has been registered successfully!" << endl;
}

// Method to log in a user
void User::loginUser(string u, string p)
{
    if (username == u && password == p)
    {
        cout << "User " << u << " has been logged in successfully!" << endl;
    }
    else
    {
        cout << "Invalid username or password. Please try again." << endl;
    }
}

int User::read()
{
    cout << "Enter User Information" << endl;
    cout << "Enter Name: ";
    getline(cin>>ws,name);
    cout << "Enter username: ";
    getline(cin>>ws,username);
    cout << "Enter email: ";
    getline(cin>>ws,email);
    cout << "Enter password: ";
    getline(cin>>ws,password);
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

void User::print() const
{
    cout << id << "\t" << name << "\t" << username << "\t" << email << "\t" << password << endl;
}

string User::printStr() const
{
    string printStr = to_string(id) + "\t" + name + "\t" + username + "\t" + email + "\t" + password;
    return printStr;
}

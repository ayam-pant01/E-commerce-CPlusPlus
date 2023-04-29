#ifndef USER_HPP
#define USER_HPP


#include <iostream>
#include <string>
using namespace std;
class User {
    private:
        static int nextId;
        int id;
        string name;
        string username;
        string password;
        string email;
    public:
        // Constructor
        User();
        User(int id,string n,string u,string e, string p);

        // Getters
        int getID();
        string getName();
        string getUsername();
        string getPassword();
        string getEmail();

        // Setters
        void setName(string n);
        void setUsername(string u);
        void setPassword(string p);
        void setEmail(string e);
        void setId(int id);

        // Other methods
        int read();
        void print() const;
        string printStr() const;

        // Method to register a user
        void registerUser();

        // Method to log in a user
        void loginUser(string u, string p);
};

#endif // USER_HPP

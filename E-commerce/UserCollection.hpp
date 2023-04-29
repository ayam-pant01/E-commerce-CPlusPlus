#ifndef USERCOLLECTION_HPP
#define USERCOLLECTION_HPP

#include "User.hpp"


class UserCollection
{
private:
    User *list;
    int count;
    int alloc;
    void grow();
    void printAllItemsToFile(ofstream& writeFile) const;

public:
    UserCollection(const string& filename);
    ~UserCollection();
    void add(User);
    void printAllItems(void);
    void readUsersFromFile(const string& filename);
    void saveUsersToFile(const string& filename) const;
    User* getUserById(int userId) const;
    User* getUserByUsername(const string& username) const;
    //User at(int index);
    int getCount()
    {
        return count;
    }

};

#endif // USERCOLLECTION_HPP

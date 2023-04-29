#include "UserCollection.hpp"
#include <fstream>
#include <sstream>

UserCollection::UserCollection(const string& filename)
{
    count=0;
    alloc=1;
    list=new User[alloc];
    readUsersFromFile(filename);

}
UserCollection::~UserCollection()
{
    delete[]list;
}

void UserCollection::add(User user)
{
    if(alloc<=count)
    {
        grow();
    }
    user.setId(count);
    list[count]=user;
    ++count;
}
void UserCollection::grow()
{
    User *temp = list;
    alloc *=2;
    list = new User[alloc];
    for(int i = 0; i<count; ++i)
        list[i] = temp[i];
    delete[] temp;
//
//    User *temp=new User[alloc*2];
//    alloc*=2;
//    for(int i=0; i<count; ++i)
//        temp[i]=list[i];
//    delete[] list;
    //list=temp;
}

void UserCollection::printAllItems(void)
{
    for(int i=0; i<count; ++i)
        list[i].print();
}

void UserCollection::printAllItemsToFile(ofstream& writeFile) const
{
    for(int i=0; i<count; ++i)
        writeFile << list[i].printStr() << endl;
}

void UserCollection::saveUsersToFile(const string& filename) const
{
    ofstream writeFile(filename);

    if (!writeFile)
    {
        cerr << "Error: unable to open writeFile!" << endl;
        return;
    }

    this->printAllItemsToFile(writeFile);
    writeFile.close();
    cout << "User list saved to file!" << endl;
}

void UserCollection::readUsersFromFile(const string& filename)
{
    bool isBossAdded = 0;
    ifstream file(filename);
    if (file.is_open())
    {
        // Check if the file is empty
        if (file.peek() == ifstream::traits_type::eof())
        {
            // File is empty, create default user
            User default_user(0, "boss", "boss", "boss@ecom.com", "boss");
            add(default_user);
            isBossAdded = 1;
            cout << "No user found.. default user boss was added." << endl;
        }
        else
        {
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string id_str, name, username, email,password;
                if (getline(iss, id_str, '\t') &&
                        getline(iss >> ws, name, '\t') &&
                        getline(iss >> ws, username, '\t') &&
                        getline(iss >> ws, email, '\t') &&
                        getline(iss >> ws, password, '\t'))
                {

                    try
                    {
                        int id = stoi(id_str);
                        User user(id, name, username, email, password);
                        add(user);
                    }
                    catch (const exception& e)
                    {
                        // Error parsing user data from file
                        cerr << "Error reading user from file: " << e.what() << endl;
                    }
                }
                else
                {
                    cout << "No user found.. need to add boss" << endl;
                }
            }
            file.close();
        }
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
    if(isBossAdded){
        saveUsersToFile(filename);
    }
}


User* UserCollection::getUserById(int userId) const
{
    for(int i=0; i<count; ++i)
    {
        if(list[i].getID() == userId)
        {
            return &list[i];
        }
    }
    return NULL;
}

User* UserCollection::getUserByUsername(const string& username) const
{
    for(int i=0; i<count; ++i)
    {
        if(list[i].getUsername() == username)
        {
            return &list[i];
        }
    }
    return NULL;
}


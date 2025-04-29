#pragma once
#include <string>

using namespace std;

class User {
private:
    int id;
    string username;
    string password;
    bool admin;
public:
    User(int id, const string& username, const string& password, bool admin = false);

    void setUsername(const string& user);
    void setPassword(const string& pass);

    string getUsername() const;
    string getPassword() const;
    bool isAdmin() const;
};

User::User(int id, const string& username, const string& password, bool admin)
    : id(id), username(username), password(password), admin(admin) {}

void User::setUsername(const string& user) { username = user;}
void User::setPassword(const string& pass) { password = pass; }

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
bool User::isAdmin() const { return admin; }
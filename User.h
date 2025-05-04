#pragma once
#include <string>

using namespace std;

class User {
private:
    int id;
    string username;
    string password;
    int admin;
public:
    User(int id, const string& username, const string& password, int admin = 0);

    void setUsername(const string& user);
    void setPassword(const string& pass);

    int getId();
    string getUsername() const;
    string getPassword() const;
    int isAdmin() const;
};

User::User(int id, const string& username, const string& password, int admin)
    : id(id), username(username), password(password), admin(admin) {}

void User::setUsername(const string& user) { username = user;}
void User::setPassword(const string& pass) { password = pass; }

int User::getId() { return id; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
int User::isAdmin() const { return admin; }
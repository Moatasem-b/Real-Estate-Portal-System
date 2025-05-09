#pragma once
#include <string>

class User {
private:
    int id;
    std::string username;
    std::string password;
    bool admin;
    bool suspended;
public:
    User(int id, const std::string& username, const std::string& password,
        bool admin = false);

    void setUsername(const std::string& user);
    void setPassword(const std::string& pass);
    void setSuspended(bool suspend);

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    bool isAdmin() const;
    bool isSuspended() const;
};

User::User(int id, const std::string& username, const std::string& password, bool admin)
    : id(id), username(username), password(password), admin(admin) {}

void User::setUsername(const std::string& username) { this->username = username;}
void User::setPassword(const std::string& password) { this->password = password; }
void User::setSuspended(bool suspend) { this->suspended = suspend; }

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
bool User::isAdmin() const { return admin; }
bool User::isSuspended() const { return suspended; }
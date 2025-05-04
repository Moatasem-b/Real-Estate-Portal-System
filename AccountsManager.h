#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include "User.h"
#include "UserAlreadyExistsException.h"
#include "UserNotFoundException.h"
#include "UserFileHandler.h" 

using namespace std;

class AccountsManager {
private:

    UserFileHandler handler;
    unordered_map<string, User> users;
    int currentUserId = 0;

    void registerUser(const string& username, const string& password);
    User login(const string& username, const string& password);
    string promptUsername();
    string promptPassword();
public:
    AccountsManager();
    ~AccountsManager();
    void registerPage();
    User loginPage();
};

AccountsManager::~AccountsManager() {

  // file save


  handler.saveUsersToFile(users);
  
}


AccountsManager::AccountsManager() {
    //users.insert({"admin", User(++currentUserId, "admin", "admin", 1)});

  handler.loadUsersFormFile(users, currentUserId);
}

void AccountsManager::registerPage() {
    string username = promptUsername();
    string password = promptPassword();

    try {
        registerUser(username, password);
        cout << "User registered successfully.\n" << endl;
    } catch (const UserAlreadyExistsException& e) {
        cout << e.what() << endl;
    }
}

void AccountsManager::registerUser(const string& username, const string& password) {
    if (users.find(username) != users.end()) {
        throw UserAlreadyExistsException("This username already exists.\n");
    }

    users.insert({username, User(++currentUserId, username, password)});
}

User AccountsManager::loginPage() {
    string username = promptUsername();
    string password = promptPassword();

    return login(username, password);
}

User AccountsManager::login(const string& username, const string& password) {
    auto it = users.find(username);
    if (it == users.end()) {
        throw UserNotFoundException("Incorrect username or password.\n");
    }

    User user = it->second;
    if (user.getPassword() != password) {
        throw UserNotFoundException("Incorrect username or password.\n");
    }

    return user;
}

string AccountsManager::promptUsername() {
    string username;

    cout << "Enter username: ";
    cin >> username;

    return username;
}

string AccountsManager::promptPassword() {
    string password;

    cout << "Enter password: ";
    cin >> password;
    
    return password;
}
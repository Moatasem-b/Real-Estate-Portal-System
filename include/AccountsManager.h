#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "User.h"
#include "../exceptions/UserAlreadyExistsException.h"
#include "../exceptions/UserNotFoundException.h"

class AccountsManager {
private:
    std::unordered_map<std::string, User> users;
    std::unordered_map<int, std::string> usersById;
    int currentUserId = 0;

    void registerUser(const std::string& username, const std::string& password);
    User login(const std::string& username, const std::string& password);
    
    std::string promptUsername();
    std::string promptPassword();
public:
    void registerPage();
    User loginPage();
    void removeUser(int id);

    std::vector<std::string> editOptions();
    void editUser(int id, int choice);
    void editUsername(User& user);
    void editPassword(User& user);

    void setUsers(const std::vector<User>& users);
    std::vector<User> getUsers() const;
};

void AccountsManager::registerPage() {
    std::string username = promptUsername();
    std::string password = promptPassword();

    try {
        registerUser(username, password);
        std::cout << "User registered successfully.\n" << std::endl;
    } catch (const UserAlreadyExistsException& e) {
        std::cout << e.what() << std::endl;
    }
}

void AccountsManager::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        throw UserAlreadyExistsException("This username already exists.\n");
    }

    users.insert({username, User(++currentUserId, username, password)});
    usersById.insert({currentUserId, username});
}

User AccountsManager::loginPage() {
    std::string username = promptUsername();
    std::string password = promptPassword();

    return login(username, password);
}

User AccountsManager::login(const std::string& username, const std::string& password) {
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

std::string AccountsManager::promptUsername() {
    std::string username;

    std::cout << "Enter username: ";
    std::cin >> username;

    return username;
}

std::string AccountsManager::promptPassword() {
    std::string password;

    std::cout << "Enter password: ";
    std::cin >> password;
    
    return password;
}

void AccountsManager::removeUser(int id) {
    auto it = usersById.find(id);

    if (it != usersById.end()) {
        users.erase(it->second);
        usersById.erase(it);
    } else {
        throw UserNotFoundException("User not found.");
    }
}

std::vector<std::string> AccountsManager::editOptions() {
    std::vector<std::string> options = {
        "1. Edit Username",
        "2. Edit Password"
    };

    return options;
}

void AccountsManager::editUser(int id, int choice) {
    auto it = usersById.find(id);

    if (it != usersById.end()) {
        User& user = users.at(it->second);
        switch (choice) {
            case 1:
                editUsername(user);
                break;
            case 2:
                editPassword(user);
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } else {
        throw UserNotFoundException("User not found.");
    }
}

void AccountsManager::editUsername(User& user) {
    std::string username;
    std::cout << "Enter new username: ";
    std::cin >> username;

    auto it = users.find(username);

    if (it == users.end()) {
        users.erase(user.getUsername());
        user.setUsername(username);
        users.insert({username, user});
        usersById[user.getId()] = username;
        std::cout << "User username updated successfully." << std::endl;
    } else {
        std::cout << "Username already exists." << std::endl;
    }
}

void AccountsManager::editPassword(User& user) {
    std::string password;
    std::cout << "Enter new password: ";

    std::cin >> password;
    user.setPassword(password);
    
    std::cout << "User password updated successfully." << std::endl;
}

void AccountsManager::setUsers(const std::vector<User>& users) {

    for (const User& user : users) {
        this->users.insert({user.getUsername(), user});
        this->usersById.insert({user.getId(), user.getUsername()});

        if (user.getId() > currentUserId) {
            currentUserId = user.getId();
        }
    }
}

std::vector<User> AccountsManager::getUsers() const {
    std::vector<User> userList;

    for (const auto& pair : users) {
        userList.push_back(pair.second);
    }

    return userList;
}

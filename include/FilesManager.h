#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#include "User.h"
#include "Property.h"

class FilesManager {
public:
    static void saveUsersToFile(const std::string& filePath, const std::vector<User>& users);
    static std::vector<User> loadUsersFromFile(const std::string& filePath);

    static void savePropertiesToFile(const std::string& filePath, const std::vector<Property>& properties);
    static std::vector<Property> loadPropertiesFromFile(const std::string& filePath);
};

void FilesManager::saveUsersToFile(const std::string& filePath, const std::vector<User>& users) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open users file for writing.");
    }

    int i = 1;
    for (const User& user : users) {
        file << user.getId() << "," << user.getUsername() << "," << user.getPassword() << "," << user.isAdmin();

        if (i < users.size()) {
            file << "\n";
        }

        i++;
    }

    file.close();
}

std::vector<User> FilesManager::loadUsersFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open users file for reading.");
    }

    std::vector<User> users;
    std::string user;

    while (std::getline(file, user)) {
        std::stringstream stream(user);
        std::string id, username, password, admin;

        std::getline(stream, id, ',');
        std::getline(stream, username, ',');
        std::getline(stream, password, ',');
        std::getline(stream, admin);

        users.push_back(User(std::stoi(id), username, password, std::stoi(admin)));
    }

    file.close();
    return users;
}

void FilesManager::savePropertiesToFile(const std::string& filePath, const std::vector<Property>& properties) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open properties file for writing.");
    }

    int i = 1;
    for (const Property& property : properties) {
        Location location = property.getLocation();

        file << property.getId() << "," << property.getName() << "," << property.getType()
             << "," << location.state << "," << location.city << "," << location.street
             << "," << location.apartmentNumber << "," << property.getRooms() << ","
             << property.getAreaInSquareMeters() << "," << property.getPrice() << ","
             << property.isHighlighted();

        if (i < properties.size()) {
            file << "\n";
        }

        i++;
    }

    file.close();
}

std::vector<Property> FilesManager::loadPropertiesFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open properties file for reading.");
    }

    std::vector<Property> properties;
    std::string property;

    while (std::getline(file, property)) {
        std::stringstream stream(property);
        std::string id, name, type, state, city, street, apartmentNumber, rooms, areaInSquareMeters, price, highlighted;

        std::getline(stream, id, ',');
        std::getline(stream, name, ',');
        std::getline(stream, type, ',');
        std::getline(stream, state, ',');
        std::getline(stream, city, ',');
        std::getline(stream, street, ',');
        std::getline(stream, apartmentNumber, ',');
        std::getline(stream, rooms, ',');
        std::getline(stream, areaInSquareMeters, ',');
        std::getline(stream, price, ',');
        std::getline(stream, highlighted);

        Location location = {state, city, street, apartmentNumber};
        PropertyDetails details = {std::stoi(rooms), std::stod(areaInSquareMeters), std::stod(price)};
        
        properties.push_back(Property(std::stoi(id), name, type, location, details, std::stoi(highlighted)));
    }

    file.close();
    return properties;
}
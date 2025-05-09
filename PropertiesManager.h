#pragma once

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>

#include "Property.h"
#include "PropertyNotFoundException.h"

using namespace std;

class PropertiesManager {
private:
    unordered_map<int, Property> properties;
    unordered_map<string, unordered_set<int>> propertiesByType;
    unordered_map<string, unordered_set<int>> propertiesByState;
    map<int, unordered_set<int>> propertiesByRooms;
    map<double, unordered_set<int>> propertiesByArea;
    map<double, unordered_set<int>> propertiesByPrice;

    queue<Property> pendingProperties;
    int currentPropertyId = 0;
public:
    void submitPropertyData(const string& name, const string& type,
        const Location& location, const PropertyDetails& details, bool isAdmin);
    void insertProperty(const Property& property);
    void removeProperty(int id);
    Property getNextPendingProperty();
    void approvePendingProperty();
    void rejectPendingProperty();

    void dispalayProperties();
    void displayPropertiesByType(const string& type);
    void displayPropertiesByState(const string& state);
    void dispalayPropertiesByRooms(int rooms);
    void dispalayPropertiesByArea(double area);
    void dispalayPropertiesByPrice(double price);
    void displayPropertiesByPriceRange(double minPrice, double maxPrice);

    void compareProperties(const vector<int>& ids);
    void highlightProperty(int id);
    void unhighlightProperty(int id);

    std::vector<std::string> editOptions();
    void editProperty(int id, int choice);
    void editName(Property& property);
    void editType(Property& property);
    void editState(Property& property);
    void editCity(Property& property);
    void editStreet(Property& property);
    void editApartmentNumber(Property& property);
    void editRooms(Property& property);
    void editArea(Property& property);
    void editPrice(Property& property);

    void initialize();
};

void PropertiesManager::submitPropertyData(const string& name, const string& type,
    const Location& location, const PropertyDetails& details, bool isAdmin) {
        Property property(++currentPropertyId, name, type, location, details);

        if (isAdmin) {
            insertProperty(property);
            cout << "The property has been added successfully." << endl;
        } else {
            pendingProperties.push(property);
            cout << "The property has been added to pending propertis successfully." << endl;
        }
}

void PropertiesManager::insertProperty(const Property& property) {
    properties.insert({property.getId(), property});
    propertiesByType[property.getType()].insert(property.getId());
    propertiesByState[property.getLocation().state].insert(property.getId());
    propertiesByRooms[property.getRooms()].insert(property.getId());
    propertiesByArea[property.getAreaInSquareMeters()].insert(property.getId());
    propertiesByPrice[property.getPrice()].insert(property.getId());
}

void PropertiesManager::removeProperty(int id) {
    auto it = properties.find(id);

    if (it != properties.end()) {
        properties.erase(it);
        propertiesByType[it->second.getType()].erase(id);
        propertiesByState[it->second.getLocation().state].erase(id);
        propertiesByRooms[it->second.getRooms()].erase(id);
        propertiesByArea[it->second.getAreaInSquareMeters()].erase(id);
        propertiesByPrice[it->second.getPrice()].erase(id);
    } else {
        throw PropertyNotFoundException("Property not found.");
    }
}

Property PropertiesManager::getNextPendingProperty() {
    if (!pendingProperties.empty()) {
        return pendingProperties.front();
    } else {
        throw PropertyNotFoundException("No pending properties available.");
    }
}

void PropertiesManager::approvePendingProperty() {
    if (!pendingProperties.empty()) {
        Property property = pendingProperties.front();
        pendingProperties.pop();
        properties.insert({property.getId(), property});
        propertiesByType[property.getType()].insert(property.getId());
        propertiesByState[property.getLocation().state].insert(property.getId());
        propertiesByRooms[property.getRooms()].insert(property.getId());
        propertiesByArea[property.getAreaInSquareMeters()].insert(property.getId());
        propertiesByPrice[property.getPrice()].insert(property.getId());
    } else {
        throw PropertyNotFoundException("No pending properties available.");
    }
}

void PropertiesManager::rejectPendingProperty() {
    if (!pendingProperties.empty()) {
        pendingProperties.pop();
    } else {
        throw PropertyNotFoundException("No pending properties available.");
    }
}

void PropertiesManager::dispalayProperties() {
    if (properties.empty()) {
        cout << "No available properties." << endl;
    } else {
        for (const auto& pair : properties) {
            const Property& property = pair.second;
            cout << "----------------------------------" << endl;
            property.display();
        }
        cout << "----------------------------------" << endl;
    }
}

void PropertiesManager::displayPropertiesByType(const string& type) {
    auto it = propertiesByType.find(type);

    if (it != propertiesByType.end()) {
        for (int id : it->second) {
            const Property& property = properties[id];
            cout << "----------------------------------" << endl;
            property.display();
        }
        cout << "----------------------------------" << endl;
    } else {
        cout << "No properties found of type " << type << "." << endl;
    }
}

void PropertiesManager::displayPropertiesByState(const string& state) {
    auto it = propertiesByState.find(state);

    if (it != propertiesByState.end()) {
        for (int id : it->second) {
            const Property& property = properties[id];
            cout << "----------------------------------" << endl;
            property.display();
        }
        cout << "----------------------------------" << endl;
    } else {
        cout << "No properties found in state " << state << "." << endl;
    }
}

void PropertiesManager::dispalayPropertiesByRooms(int rooms) {
    auto it = propertiesByRooms.find(rooms);

    if (it != propertiesByRooms.end()) {
        for (int id : it->second) {
            const Property& property = properties[id];
            cout << "----------------------------------" << endl;
            property.display();
        }
        cout << "----------------------------------" << endl;
    } else {
        cout << "No properties found with " << rooms << " rooms." << endl;
    }
}

void PropertiesManager::dispalayPropertiesByArea(double area) {
    auto it = propertiesByArea.find(area);

    if (it != propertiesByArea.end()) {
        for (int id : it->second) {
            const Property& property = properties[id];
            cout << "----------------------------------" << endl;
            property.display();
        }
        cout << "----------------------------------" << endl;
    } else {
        cout << "No properties found with area of " << area << " square meters." << endl;
    }
}

void PropertiesManager::dispalayPropertiesByPrice(double price) {
    auto it = propertiesByPrice.find(price);

    if (it != propertiesByPrice.end()) {
        for (int id : it->second) {
            const Property& property = properties[id];
            cout << "----------------------------------" << endl;
            property.display();
        }
        cout << "----------------------------------" << endl;
    } else {
        cout << "No properties found with price of $" << price << "." << endl;
    }
}

void PropertiesManager::displayPropertiesByPriceRange(double minPrice, double maxPrice) {
    auto start = propertiesByPrice.lower_bound(minPrice);
    auto end = propertiesByPrice.upper_bound(maxPrice);

    if (start != end) {
        for (auto it = start; it != end; ++it) {
            for (int id : it->second) {
                const Property& property = properties[id];
                cout << "----------------------------------" << endl;
                property.display();
            }
        }
        cout << "----------------------------------" << endl;
    } else {
        cout << "No properties found in the price range $" << minPrice << " - $" << maxPrice << "." << endl;
    }
}

void PropertiesManager::compareProperties(const vector<int>& ids) {
    map<int, double> pricePerArea;

    for (int id : ids) {
        auto it = properties.find(id);

        cout << "----------------------------------" << endl;
        if (it != properties.end()) {
            const Property& property = it->second;
            pricePerArea.insert({id, property.getPrice() / property.getAreaInSquareMeters()});
            property.display();
        } else {
            cout << "Property with ID " << id << " not found." << endl;
        }
    }

    if (!pricePerArea.empty()) {
        cout << "----------------------------------" << endl;
        cout << "Price per area comparison:" << endl;

        for (const auto& pair : pricePerArea) {
            cout << "Property ID: " << pair.first << ", Price per area: $"
                 << fixed << setprecision(2) << pair.second << endl;
        }
        cout << "----------------------------------" << endl;
    }
}

void PropertiesManager::highlightProperty(int id) {
    auto it = properties.find(id);

    if (it != properties.end()) {
        it->second.setHighlighted(true);
        // cout << "Property with ID " << id << " has been highlighted." << endl;
    } else {
        // cout << "Property with ID " << id << " not found." << endl;
        throw PropertyNotFoundException("Property not found.");
    }
}

void PropertiesManager::unhighlightProperty(int id) {
    auto it = properties.find(id);

    if (it != properties.end()) {
        it->second.setHighlighted(false);
        // cout << "Property with ID " << id << " has been unhighlighted." << endl;
    } else {
        // cout << "Property with ID " << id << " not found." << endl;
        throw PropertyNotFoundException("Property not found.");
    }
}

std::vector<std::string> PropertiesManager::editOptions() {
    std::vector<string> options = {
        "1. Edit Name",
        "2. Edit Type",
        "3. Edit State",
        "4. Edit City",
        "5. Edit Street",
        "6. Edit Apartment Number",
        "7. Edit Rooms",
        "8. Edit Area",
        "9. Edit Price"
    };

    return options;
}

void PropertiesManager::editProperty(int id, int choice) {
    auto it = properties.find(id);

    if (it != properties.end()) {
        Property& property = it->second;
        removeProperty(id);

        switch (choice) {
            case 1:
                editName(property);
                break;
            case 2:
                editType(property);
                break;
            case 3:
                editState(property);
                break;
            case 4:
                editCity(property);
                break;
            case 5:
                editStreet(property);
                break;
            case 6:
                editApartmentNumber(property);
                break;
            case 7:
                editRooms(property);
                break;
            case 8:
                editArea(property);
                break;
            case 9:
                editPrice(property);
                break;
            default:
                std::cout << "Invalid choice." << endl;
        }

        insertProperty(property);
    } else {
        throw PropertyNotFoundException("Property not found.");
    }
}

void PropertiesManager::editName(Property& property) {
    string name;
    std::cout << "Enter new property name: ";

    std::cin.ignore();
    std::getline(std::cin, name);
    property.setName(name);

    std::cout << "Property name updated successfully." << std::endl;
}

void PropertiesManager::editType(Property& property) {
    string type;
    std::cout << "Enter new property type: ";

    std::cin.ignore();
    std::getline(std::cin, type);
    property.setType(type);

    std::cout << "Property type updated successfully." << std::endl;
}

void PropertiesManager::editState(Property& property) {
    string state;
    std::cout << "Enter new state: ";

    std::cin.ignore();
    std::getline(std::cin, state);
    Location location = property.getLocation();
    location.state = state;
    property.setLocation(location);

    std::cout << "Property state updated successfully." << std::endl;
}

void PropertiesManager::editCity(Property& property) {
    string city;
    std::cout << "Enter new city: ";

    std::cin.ignore();
    std::getline(std::cin, city);
    Location location = property.getLocation();
    location.city = city;
    property.setLocation(location);
    
    std::cout << "Property city updated successfully." << std::endl;
}

void PropertiesManager::editStreet(Property& property) {
    string street;
    std::cout << "Enter new street: ";

    std::cin.ignore();
    std::getline(std::cin, street);
    Location location = property.getLocation();
    location.street = street;
    property.setLocation(location);

    std::cout << "Property street updated successfully." << std::endl;
}

void PropertiesManager::editApartmentNumber(Property& property) {
    string apartmentNumber;
    std::cout << "Enter new apartment number: ";

    std::cin.ignore();
    std::getline(std::cin, apartmentNumber);
    Location location = property.getLocation();
    location.apartmentNumber = apartmentNumber;
    property.setLocation(location);

    std::cout << "Property number updated successfully." << std::endl;
}

void PropertiesManager::editRooms(Property& property) {
    int rooms;
    std::cout << "Enter new number of rooms: ";

    std::cin >> rooms;
    property.setRooms(rooms);

    std::cout << "Property rooms updated successfully." << std::endl;
}

void PropertiesManager::editArea(Property& property) {
    double area;
    std::cout << "Enter new area in square meters: ";

    std::cin >> area;
    property.setAreaInSquareMeters(area);

    std::cout << "Property area updated successfully." << std::endl;
}

void PropertiesManager::editPrice(Property& property) {
    double price;
    std::cout << "Enter new price: ";

    std::cin >> price;
    property.setPrice(price);

    std::cout << "Property price updated successfully." << std::endl;
}

void PropertiesManager::initialize() {
    submitPropertyData("Cozy Apartment", "Apartment", {"California", "Los Angeles", "Sunset Blvd", "101"}, {2, 55.5, 250000}, true);
    submitPropertyData("Spacious House", "House", {"California", "Los Angeles", "Elm St", "202"}, {4, 150.0, 850000}, true);
    // submitPropertyData("Luxury Condo", "Condo", {"California", "San Francisco", "Market St", "303"}, {3, 80.0, 600000}, true);
    // submitPropertyData("Compact Studio", "Apartment", {"California", "Los Angeles", "Sunset Blvd", "104"}, {1, 35.0, 150000}, true);
    // submitPropertyData("Modern Villa", "Villa", {"Texas", "Austin", "Lake View Rd", "505"}, {5, 200.0, 1200000}, true);
    submitPropertyData("Traditional House", "House", {"Texas", "Houston", "Main St", "606"}, {4, 180.0, 700000}, false);
    submitPropertyData("Cozy Cabin", "Cabin", {"Colorado", "Denver", "Mountain Rd", "707"}, {2, 100.0, 400000}, false);
    // submitPropertyData("City Apartment", "Apartment", {"New York", "New York", "5th Ave", "808"}, {2, 65.0, 300000}, false);
    // submitPropertyData("Penthouse Suite", "Condo", {"New York", "New York", "Park Ave", "909"}, {3, 120.0, 2000000}, false);
    // submitPropertyData("Family House", "House", {"California", "San Francisco", "Mission St", "1010"}, {4, 160.0, 900000}, false);

    currentPropertyId = 3;
}
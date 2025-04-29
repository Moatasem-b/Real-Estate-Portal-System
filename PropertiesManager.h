#pragma once

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
#include <vector>

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
    void submitPropertyData(const string& name, const string& type, const Location& location, const PropertyDetails& details);
    void removeProperty(int id);
    Property getNextPendingProperty();
    void approvePendingProperty();
    void rejectPendingProperty();
    Property getPropertyById(int id);

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

    void initialize();
};

void PropertiesManager::submitPropertyData(const string& name, const string& type, const Location& location, const PropertyDetails& details) {
    Property property(++currentPropertyId, name, type, location, details);
    pendingProperties.push(property);
    cout << "The property has been added to pending propertis successfully." << endl;
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

        cout << "Property with ID " << id << " has been removed." << endl;
    } else {
        cout << "Property with ID " << id << " not found." << endl;
    
    }
}

Property PropertiesManager::getNextPendingProperty() {
    if (!pendingProperties.empty()) {
        return pendingProperties.front();
    } else {
        throw runtime_error("No pending properties available.");
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
        throw runtime_error("No pending properties available.");
    }
}

void PropertiesManager::rejectPendingProperty() {
    if (!pendingProperties.empty()) {
        pendingProperties.pop();
    } else {
        throw runtime_error("No pending properties available.");
    }
}

Property PropertiesManager::getPropertyById(int id) {
    auto it = properties.find(id);

    if (it != properties.end()) {
        return it->second;
    } else {
        const char* message = ("Property with ID " + to_string(id) + "not found.").c_str();
        throw PropertyNotFoundException(message);
    }
}

void PropertiesManager::dispalayProperties() {
    if (properties.empty()) {
        cout << "No properties available." << endl;
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
        cout << "Property with ID " << id << " has been highlighted." << endl;
    } else {
        cout << "Property with ID " << id << " not found." << endl;
    }
}

void PropertiesManager::unhighlightProperty(int id) {
    auto it = properties.find(id);

    if (it != properties.end()) {
        it->second.setHighlighted(false);
        cout << "Property with ID " << id << " has been unhighlighted." << endl;
    } else {
        cout << "Property with ID " << id << " not found." << endl;
    }
}

void PropertiesManager::initialize() {
    submitPropertyData("Cozy Apartment", "Apartment", {"California", "Los Angeles", "Sunset Blvd", "101"}, {2, 55.5, 250000});
    submitPropertyData("Spacious House", "House", {"California", "Los Angeles", "Elm St", "202"}, {4, 150.0, 850000});
    submitPropertyData("Luxury Condo", "Condo", {"California", "San Francisco", "Market St", "303"}, {3, 80.0, 600000});
    submitPropertyData("Compact Studio", "Apartment", {"California", "Los Angeles", "Sunset Blvd", "104"}, {1, 35.0, 150000});
    submitPropertyData("Modern Villa", "Villa", {"Texas", "Austin", "Lake View Rd", "505"}, {5, 200.0, 1200000});
    submitPropertyData("Traditional House", "House", {"Texas", "Houston", "Main St", "606"}, {4, 180.0, 700000});
    submitPropertyData("Cozy Cabin", "Cabin", {"Colorado", "Denver", "Mountain Rd", "707"}, {2, 100.0, 400000});
    submitPropertyData("City Apartment", "Apartment", {"New York", "New York", "5th Ave", "808"}, {2, 65.0, 300000});
    submitPropertyData("Penthouse Suite", "Condo", {"New York", "New York", "Park Ave", "909"}, {3, 120.0, 2000000});
    submitPropertyData("Family House", "House", {"California", "San Francisco", "Mission St", "1010"}, {4, 160.0, 900000});

    currentPropertyId = 10;
}
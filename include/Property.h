#pragma once

#include <iostream>
#include <iomanip>
#include <string>

struct Location {
    std::string state;
    std::string city;
    std::string street;
    std::string apartmentNumber;
};

struct PropertyDetails {
    int rooms;
    double areaInSquareMeters;
    double price;
};

class Property {
private:
    int id;
    std::string name;
    std::string type;
    Location location;
    PropertyDetails details;
    bool highlighted;
public:
    Property();
    Property(int id, const std::string& name, const std::string& type, const Location& location, const PropertyDetails& details,
    bool highlighted = false);

    void setName(const std::string& name);
    void setType(const std::string& type);
    void setLocation(const Location& location);
    void setRooms(int rooms);
    void setAreaInSquareMeters(double areaInSquareMeters);
    void setPrice(double price);
    void setHighlighted(bool highlighted);

    int getId() const;
    std::string getName() const;
    std::string getType() const;
    Location getLocation() const;
    int getRooms() const;
    double getAreaInSquareMeters() const;
    double getPrice() const;
    bool isHighlighted() const;

    void display() const;
};

Property::Property() = default;
Property::Property(int id, const std::string& name, const std::string& type, const Location& location, const PropertyDetails& details, bool highlighted)
    : id(id), name(name), type(type), location(location), details(details), highlighted(highlighted) {}

void Property::setName(const std::string& name) { this->name = name; }
void Property::setType(const std::string& type) { this->type = type; }
void Property::setLocation(const Location& location) { this->location = location; }
void Property::setRooms(int rooms) { this->details.rooms = rooms; }
void Property::setAreaInSquareMeters(double areaInSquareMeters) {
    this->details.areaInSquareMeters = areaInSquareMeters;
}
void Property::setPrice(double price) { this->details.price = price; }
void Property::setHighlighted(bool highlighted) { this->highlighted = highlighted;}

int Property::getId() const { return id; }
std::string Property::getName() const { return name; }
std::string Property::getType() const { return type; }
Location Property::getLocation() const { return location; }
int Property::getRooms() const { return details.rooms; }
double Property::getAreaInSquareMeters() const { return details.areaInSquareMeters; }
double Property::getPrice() const { return details.price; }
bool Property::isHighlighted() const { return highlighted; }

void Property::display() const {
    const char* highlight = (highlighted) ? " [HOT🔥]" : "";
    std::cout << "ID: " << id << "\nName: " << name << highlight
         << "\nType: " << type
         << "\nLocation: " << location.state << ", " << location.city
         << ", " << location.street << ", " << location.apartmentNumber
         << "\nRooms: " << details.rooms << "\nArea: " << details.areaInSquareMeters
         << "m²\nPrice: $" << std::fixed << std::setprecision(2) << details.price << std::endl;
}
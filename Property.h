#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Location {
    string state;
    string city;
    string street;
    string apartmentNumber;
};

struct PropertyDetails {
    int rooms;
    double areaInSquareMeters;
    double price;
};

class Property {
private:
    int id;
    string name;
    string type;
    Location location;
    PropertyDetails details;
    bool highlighted;
public:
    Property();
    Property(int id, const string& name, const string& type, const Location& location,
        const PropertyDetails& details, bool highlighted = false);

    void setName(const string& name);
    void setType(const string& type);
    void setLocation(const Location& location);
    void setRooms(int rooms);
    void setAreaInSquareMeters(double areaInSquareMeters);
    void setPrice(double price);
    void setHighlighted(bool highlighted);

    int getId() const;
    string getName() const;
    string getType() const;
    Location getLocation() const;
    int getRooms() const;
    double getAreaInSquareMeters() const;
    double getPrice() const;
    bool isHighlighted() const;

    void display() const;
};

Property::Property() = default;
Property::Property(int id, const string& name, const string& type,
    const Location& location, const PropertyDetails& details, bool highlighted)
    : id(id), name(name), type(type), location(location), details(details),
    highlighted(highlighted) {}

void Property::setName(const string& name) { this->name = name; }
void Property::setType(const string& type) { this->type = type; }
void Property::setLocation(const Location& location) { this->location = location; }
void Property::setRooms(int rooms) { this->details.rooms = rooms; }
void Property::setAreaInSquareMeters(double areaInSquareMeters) {
    this->details.areaInSquareMeters = areaInSquareMeters;
}
void Property::setPrice(double price) { this->details.price = price; }
void Property::setHighlighted(bool highlighted) { this->highlighted = highlighted;}

int Property::getId() const { return id; }
string Property::getName() const { return name; }
string Property::getType() const { return type; }
Location Property::getLocation() const { return location; }
int Property::getRooms() const { return details.rooms; }
double Property::getAreaInSquareMeters() const { return details.areaInSquareMeters; }
double Property::getPrice() const { return details.price; }
bool Property::isHighlighted() const { return highlighted; }

void Property::display() const {
    const char* highlight = (highlighted) ? " [HOT]" : "";
    cout << "ID: " << id << "\nName: " << name << highlight
         << "\nType: " << type
         << "\nLocation: " << location.state << ", " << location.city
         << ", " << location.street << ", " << location.apartmentNumber
         << "\nRooms: " << details.rooms << "\nArea: " << details.areaInSquareMeters
         << "m²\nPrice: $" << fixed << setprecision(2) << details.price << endl;
}
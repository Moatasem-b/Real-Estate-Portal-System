#pragma once
#include "Property.h"

class PropertyEditor {
private:
public:
    void editName(Property& property);
    void editType(Property& property);
    void editState(Property& property);
    void editCity(Property& property);
    void editStreet(Property& property);
    void editApartmentNumber(Property& property);
    void editRooms(Property& property);
    void editArea(Property& property);
    void editPrice(Property& property);
};

void PropertyEditor::editName(Property& property) {
    string name;
    cout << "Enter new property name: ";
    cin.ignore();
    getline(cin, name);
    property.setName(name);
}

void PropertyEditor::editType(Property& property) {
    string type;
    cout << "Enter new property type: ";
    cin.ignore();
    getline(cin, type);
    property.setType(type);
}

void PropertyEditor::editState(Property& property) {
    string state;
    cout << "Enter new state: ";
    cin.ignore();
    getline(cin, state);
    Location location = property.getLocation();
    location.state = state;
    property.setLocation(location);
}

void PropertyEditor::editCity(Property& property) {
    string city;
    cout << "Enter new city: ";
    cin.ignore();
    getline(cin, city);
    Location location = property.getLocation();
    location.city = city;
    property.setLocation(location);
}

void PropertyEditor::editStreet(Property& property) {
    string street;
    cout << "Enter new street: ";
    cin.ignore();
    getline(cin, street);
    Location location = property.getLocation();
    location.street = street;
    property.setLocation(location);
}

void PropertyEditor::editApartmentNumber(Property& property) {
    string apartmentNumber;
    cout << "Enter new apartment number: ";
    cin.ignore();
    getline(cin, apartmentNumber);
    Location location = property.getLocation();
    location.apartmentNumber = apartmentNumber;
    property.setLocation(location);
}

void PropertyEditor::editRooms(Property& property) {
    int rooms;
    cout << "Enter new number of rooms: ";
    cin >> rooms;
    property.setRooms(rooms);
}

void PropertyEditor::editArea(Property& property) {
    double area;
    cout << "Enter new area in square meters: ";
    cin >> area;
    property.setAreaInSquareMeters(area);
}

void PropertyEditor::editPrice(Property& property) {
    double price;
    cout << "Enter new price: ";
    cin >> price;
    property.setPrice(price);
}
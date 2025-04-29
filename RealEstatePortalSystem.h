#pragma once

#include "AccountsManager.h"
#include "PropertiesManager.h"

using namespace std;

class RealEstatePortalSystem {
private:
    AccountsManager accountsManager;
    PropertiesManager propertiesManager;

    int promptChoice(int min, int max);
    void handleHomePageChoice(int choice);
    void adminPage(User& admin);
    vector<string> adminOptions();
    void displayOptions(const vector<string>& options);
    void handleAdminChoice(int choice, User& admin);
    vector<string> userManagementOptions();
    void manageProperties();
    vector<string> propertyManagementOptions();
    void processPendingProperties();
    void processNextPendingProperty();
    void handlePropertyManagementChoice(int choice, User& admin);
    void removePropertyById();
    void setHighlightById(bool highlight);
    void editPropertyById();

    void userPage(User& user);
    vector<string> userMenuOptions();
    void handleUserChoice(int choice, User& user);
    void submitNewProperty();
    void searchPropertiesWithFilters();
    vector<string> searchFilterOptions();
    void compareProperties();

    int promptPropertyId();
public:
    void start();
    void homePage();
};

void RealEstatePortalSystem::start() {

}

void RealEstatePortalSystem::homePage() {
    cout << "Welcome to the Real Estate Portal!" << endl;
    cout << "----------------------------------\n" << endl;

    int choice = 0;
    propertiesManager.initialize();

    do {
        cout << "1. Register\n" << "2. Login\n" << "3. Exit\n" << endl;
        choice = promptChoice(1, 3);
        cout << endl;
        handleHomePageChoice(choice);
    } while (choice != 3);    
}

int RealEstatePortalSystem::promptChoice(int min, int max) {
    int choice;

    do {
        cout << "Enter choice between " << min << " and " << max << ": ";
        cin >> choice;

        if (choice < min || choice > max) {
            cout << "Invalid choice. Please try again.\n" << endl;
        }
    } while (choice < min || choice > max);

    return choice;
}

void RealEstatePortalSystem::handleHomePageChoice(int choice) {
    switch (choice) {
        case 1:
            accountsManager.registerPage();
            break;
        case 2:
            try {
                User user = accountsManager.loginPage();
                if (user.isAdmin()) {
                    adminPage(user);
                } else {
                    userPage(user);
                }
            } catch (const UserNotFoundException& e) {
                cout << e.what() << endl;
            }
            break;
        case 3:
            cout << "Exiting the system..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void RealEstatePortalSystem::adminPage(User& admin) {
    cout << "\nWelcome, " << admin.getUsername() << "!" << endl;

    vector<string> options = adminOptions();
    int choice = 0;

    do {
        displayOptions(options);
        choice = promptChoice(1, options.size());
        handleAdminChoice(choice, admin);
    } while (choice != options.size());
}

vector<string> RealEstatePortalSystem::adminOptions() {
    vector<string> options = {
        "1. Manage Users",
        "2. Manage Properties",
        "3. Process Pending Properties",
        "4. Logout"
    };

    return options;
}

void RealEstatePortalSystem::displayOptions(const vector<string>& options) {
    cout << "----------------------------------" << endl;
    for (const string& option : options) {
        cout << option << endl;
    }
    cout << "----------------------------------" << endl;
}

void RealEstatePortalSystem::handleAdminChoice(int choice, User& admin) {
    switch (choice) {
        case 1:
            // Manage Users
            break;
        case 2:
            // Manage Properties
            break;
        case 3:
            processPendingProperties();
            break;
        case 4:
            cout << "Logging out...\n" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again.\n" << endl;
    }
}

vector<string> RealEstatePortalSystem::userManagementOptions() {
    vector<string> options = {

    };

    return options;
}

void RealEstatePortalSystem::manageProperties() {
    vector<string> options = propertyManagementOptions();
    displayOptions(options);
    int choice = promptChoice(1, options.size());
}

vector<string> RealEstatePortalSystem::propertyManagementOptions() {
    vector<string> options = {
        "1. Submit New Property",
        "2. Remove Property",
        "3. Edit Property",
        "4. Highlight Property",
        "5. Unhighlight Property"
    };

    return options;
}

void RealEstatePortalSystem::handlePropertyManagementChoice(int choice, User& admin) {
    switch (choice) {
        case 1:
            submitNewProperty();
            break;
        case 2:
            removePropertyById();
            break;
        case 3:
            // Edit Property
            break;
        case 4:
            setHighlightById(true);
            break;
        case 5:
            setHighlightById(false);
            break;
        default:
            cout << "Invalid choice. Please try again.\n" << endl;
    }
}

void RealEstatePortalSystem::removePropertyById() {
    int id = promptPropertyId();
    propertiesManager.removeProperty(id);
}

int RealEstatePortalSystem::promptPropertyId() {
    cout << "Enter property ID: ";
    int id;
    cin >> id;

    return id;
}

void RealEstatePortalSystem::setHighlightById(bool highlight) {
    int id = promptPropertyId();

    if (highlight) {
        propertiesManager.highlightProperty(id);
    } else {
        propertiesManager.unhighlightProperty(id);
    }
}

void RealEstatePortalSystem::editPropertyById() {


}

void RealEstatePortalSystem::processPendingProperties() {
    char choice;

    do {
        try {
            processNextPendingProperty();
            cout << "Do you want to process the next pending property? (y/n): ";
            cin >> choice;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
            choice = 'n';
        }
    } while (choice == 'y' || choice == 'Y');
}

void RealEstatePortalSystem::processNextPendingProperty() {
    Property property = propertiesManager.getNextPendingProperty();
    property.display();

    cout << "Do you want to approve this property? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        propertiesManager.approvePendingProperty();
        cout << "The Property has been approved." << endl;
    } else {
        propertiesManager.rejectPendingProperty();
        cout << "The Property has been rejected." << endl;
    }
}

void RealEstatePortalSystem::userPage(User& user) {
    cout << "\nWelcome, " << user.getUsername() << "!" << endl;

    vector<string> options = userMenuOptions();
    int choice = 0;

    do {
        displayOptions(options);
        choice = promptChoice(1, options.size());
        handleUserChoice(choice, user);
    } while (choice != options.size());
}

vector<string> RealEstatePortalSystem::userMenuOptions() {
    vector<string> options = {
        "1. Manage Profile",
        "2. Submit New Property",
        "3. Display Properties",
        "4. Search Properties with Filters",
        "5. Compare Properties",
        "6. Logout"
    };
    
    return options;
}

void RealEstatePortalSystem::handleUserChoice(int choice, User& user) {
    switch (choice) {
        case 1:
            // Manage Profile
            break;
        case 2:
            submitNewProperty();
            break;
        case 3:
            propertiesManager.dispalayProperties();
            break;
        case 4:
            searchPropertiesWithFilters();
            break;
        case 5:
            compareProperties();
            break;
        case 6:
            cout << "Logging out...\n" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again.\n" << endl;
    }
}

void RealEstatePortalSystem::submitNewProperty() {
    string name, type, state, city, street, apartmentNumber;
    int rooms;
    double areaInSquareMeters, price;

    cout << "----------------------------------" << endl;
    cout << "Enter property name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter property type: ";
    getline(cin, type);

    cout << "Enter property state: ";
    getline(cin, state);

    cout << "Enter property city: ";
    getline(cin, city);

    cout << "Enter property street: ";
    getline(cin, street);

    cout << "Enter property apartement No.: ";
    getline(cin, apartmentNumber);

    cout << "Enter number of rooms: ";
    cin >> rooms;

    cout << "Enter property area in square meters: ";
    cin >> areaInSquareMeters;

    cout << "Enter property price: $";
    cin >> price;

    Location location = { state, city, street, apartmentNumber };
    PropertyDetails details = {rooms, areaInSquareMeters, price};
    propertiesManager.submitPropertyData(name, type, location, details);
}

void RealEstatePortalSystem::searchPropertiesWithFilters() {
    vector<string> options = searchFilterOptions();
    displayOptions(options);
    int choice = promptChoice(1, options.size());
    cin.ignore();

    if (choice == 1) {
        string type;
        cout << "Enter property type: ";
        getline(cin, type);
        propertiesManager.displayPropertiesByType(type);
    } else if (choice == 2) {
        string state;
        cout << "Enter property state: ";
        getline(cin, state);
        propertiesManager.displayPropertiesByState(state);
    } else if (choice == 3) {
        int rooms;
        cout << "Enter number of rooms: ";
        cin >> rooms;
        propertiesManager.dispalayPropertiesByRooms(rooms);
    } else if (choice == 4) {
        double area;
        cout << "Enter area in square meters: ";
        cin >> area;
        propertiesManager.dispalayPropertiesByArea(area);
    } else if (choice == 5) {
        double price;
        cout << "Enter price: ";
        cin >> price;
        propertiesManager.dispalayPropertiesByPrice(price);
    } else if (choice == 6) {
        double minPrice, maxPrice;
        cout << "Enter minimum price: ";
        cin >> minPrice;
        cout << "Enter maximum price: ";
        cin >> maxPrice;
        propertiesManager.displayPropertiesByPriceRange(minPrice, maxPrice);
    }
}

vector<string> RealEstatePortalSystem::searchFilterOptions() {
    vector<string> options = {
        "1. Search by Type",
        "2. Search by State",
        "3. Search by Rooms",
        "4. Search by Area",
        "5. Search by Price",
        "6. Search by Price Range"
    };

    return options;
}

void RealEstatePortalSystem::compareProperties() {
    vector<int> propertyIds;
    int id = -1;

    cout << "Enter property IDs to compare (0 to stop): ";
    while (id != 0) {
        cin >> id;
        if (id != 0) {
            propertyIds.push_back(id);
        }
    }

    if (propertyIds.size() >= 2) {
        propertiesManager.compareProperties(propertyIds);
    } else {
        cout << "At least two properties are required for comparison." << endl;
    }
}


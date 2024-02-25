#include <iostream> // For input and output
#include <fstream> // For file input and output
#include <string> // For string manipulation
#include <vector> 
#include <iomanip> // For formatting output
#include <algorithm> // For algorithms like remove

#ifdef _WIN32
#include <windows.h> // For Windows system commands
#else
#include <cstdlib>
#endif

using namespace std;

// Structure for a planet in the solar system
struct Planet {
    string name;
    double distanceFromEarth; // Distance from Earth in millions of kilometers
};

// Structure for a crew member role
struct Role {
    string name;
};

// Structure for a spaceship option
struct SpaceshipOption {
    string name;
    double speed; // Speed in km/h
    double capacity; // Capacity of fuel tank in liters
};

// List of planets in the solar system
vector<Planet> solarSystem = {
    {"Mercury", 77.3},
    {"Venus", 38.2},
    {"Earth", 0.0},
    {"Mars", 54.6},
    {"Jupiter", 588.0},
    {"Saturn", 1200.0},
    {"Uranus", 2600.0},
    {"Neptune", 4350.0},
};

// List of crew member roles
vector<Role> crewRoles = {
    {"Captain"},
    {"Navigator"},
    {"Engineer"},
    {"Pilot"},
    {"Medic"},
    {"Scientist"},
    {"Crew Member"} // Newly added role
};

// List of spaceship options
vector<SpaceshipOption> spaceshipOptions = {
    {"Falcon", 100000, 10000},
    {"Starblazer", 120000, 12000},
    {"Nebula Voyager", 90000, 8000},
    {"Galaxy Runner", 110000, 11000},
    {"Cosmo Strider", 95000, 9000},
    {"Stellar Cruiser", 115000, 10000}
};

// Enumeration for main menu options
enum MainMenuOptions {
    NEW_EXPEDITION = 1,
    VIEW_EXPEDITIONS,
    EDIT_EXPEDITION,
    DELETE_EXPEDITION,
    VIEW_CREW_MEMBERS,
    ADD_CREW_MEMBER,
    REMOVE_CREW_MEMBER,
    VIEW_CREW_MEMBERS_WITH_ROLES,
    SEARCH_EXPEDITIONS,
    SAVE_DATA,
    LOAD_DATA,
    CALCULATE_DISTANCE,
    EXIT
};

// Enumeration for expedition status
enum ExpeditionStatus {
    PLANNED,
    IN_PROGRESS,
    COMPLETED,
    CANCELED
};

// Structure for a crew member
struct CrewMember {
    string name;
    string role;
};

// Structure for an expedition
struct Expedition {
    int id;
    string name;
    string destination;
    ExpeditionStatus status;
    vector<CrewMember> crewMembers;
    double distance;

    // Overloading the equality operator for comparing expeditions
    bool operator==(const Expedition& other) const {
        return id == other.id;
    }
};

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to display the main menu and get user choice
int displayMainMenu() {
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Space Expedition Manager" << endl;
    cout << "======================================================================================" << endl;
    cout << "1. New Expedition" << endl;
    cout << "2. View Expeditions" << endl;
    cout << "3. Edit Expedition" << endl;
    cout << "4. Delete Expedition" << endl;
    cout << "5. View Crew Members" << endl;
    cout << "6. Add Crew Member" << endl;
    cout << "7. Remove Crew Member" << endl;
    cout << "8. View Crew Members With Roles" << endl;
    cout << "9. Search Expeditions" << endl;
    cout << "10. Save Data" << endl;
    cout << "11. Load Data" << endl;
    cout << "12. Calculate Distance" << endl;
    cout << "13. Exit" << endl;
    cout << "======================================================================================" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

// Function to display spaceship options and get user choice
int displaySpaceshipOptions() {
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Select Spaceship" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < spaceshipOptions.size(); ++i) {
        cout << i + 1 << ". " << spaceshipOptions[i].name << endl;
    }
    cout << "======================================================================================" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

// Function to display planet options and get user choice
int displayPlanetOptions() {
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Select Destination Planet" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < solarSystem.size(); ++i) {
        cout << i + 1 << ". " << solarSystem[i].name << endl;
    }
    cout << "======================================================================================" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

// Function to create a new expedition
void createExpedition(vector<Expedition>& expeditions) {
    cout << "Enter expedition name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    int spaceshipChoice = displaySpaceshipOptions();
    if (spaceshipChoice < 1 || spaceshipChoice > spaceshipOptions.size()) {
        cout << "Invalid spaceship choice!" << endl;
        return;
    }

    int planetChoice = displayPlanetOptions();
    if (planetChoice < 1 || planetChoice > solarSystem.size()) {
        cout << "Invalid planet choice!" << endl;
        return;
    }

    int planetIndex = planetChoice - 1;

    cout << "Selected destination planet: " << solarSystem[planetIndex].name << endl;

    string destination = solarSystem[planetIndex].name;

    cout << "Enter expedition status (1 for Planned, 2 for In Progress, 3 for Completed, 4 for Canceled): ";
    int status;
    cin >> status;

    ExpeditionStatus expeditionStatus = static_cast<ExpeditionStatus>(status);

    vector<CrewMember> crewMembers;

    cout << "Enter the number of crew members: ";
    int numCrewMembers;
    cin >> numCrewMembers;

    if (numCrewMembers > 15) {
        cout << "Expedition cannot have more than 15 crew members." << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < numCrewMembers; i++) {
        CrewMember crewMember;
        cout << "Enter crew member name: ";
        getline(cin, crewMember.name);

        cout << "Select crew member role:" << endl;
        for (int j = 0; j < crewRoles.size(); ++j) {
            cout << j + 1 << ". " << crewRoles[j].name << endl;
        }
        cout << "Enter your choice: ";
        int roleChoice;
        cin >> roleChoice;
        if (roleChoice < 1 || roleChoice > crewRoles.size()) {
            cout << "Invalid role choice!" << endl;
            return;
        }
        crewMember.role = crewRoles[roleChoice - 1].name;

        crewMembers.push_back(crewMember);
    }

    Expedition expedition;
    expedition.id = expeditions.size() + 1;
    expedition.name = name;
    expedition.destination = destination;
    expedition.status = expeditionStatus;
    expedition.crewMembers = crewMembers;

    double distance = 0.0;
    for (int i = 0; i < planetIndex; ++i) {
        distance += solarSystem[i].distanceFromEarth;
    }
    expedition.distance = distance;

    expeditions.push_back(expedition);

    cout << "Expedition created successfully!" << endl;
}

// Function to view all expeditions
void viewExpeditions(vector<Expedition> expeditions) {
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Expeditions" << endl;
    cout << "======================================================================================" << endl;
    cout << "ID\tName\tDestination\tStatus" << endl;
    for (Expedition expedition : expeditions) {
        cout << expedition.id << "\t" << expedition.name << "\t" << expedition.destination << "\t";

        string status;
        switch (expedition.status) {
        case PLANNED:
            status = "Planned";
            break;
        case IN_PROGRESS:
            status = "In Progress";
            break;
        case COMPLETED:
            status = "Completed";
            break;
        case CANCELED:
            status = "Canceled";
            break;
        }

        cout << status << endl;
    }

    cout << "======================================================================================" << endl;
}

// Function to edit an existing expedition
void editExpedition(vector<Expedition>& expeditions) {
    cout << "Enter the ID of the expedition to edit: ";
    int id;
    cin >> id;

    Expedition* expedition = nullptr;
    for (Expedition& exp : expeditions) {
        if (exp.id == id) {
            expedition = &exp;
            break;
        }
    }

    if (expedition == nullptr) {
        cout << "Expedition not found!" << endl;
        return;
    }

    cout << "Enter new expedition name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    cout << "Enter new expedition destination: ";
    string destination;
    getline(cin, destination);

    cout << "Enter new expedition status (1 for Planned, 2 for In Progress, 3 for Completed, 4 for Canceled): ";
    int status;
    cin >> status;

    ExpeditionStatus expeditionStatus = static_cast<ExpeditionStatus>(status);

    expedition->name = name;
    expedition->destination = destination;
    expedition->status = expeditionStatus;

    cout << "Expedition updated successfully!" << endl;
}

// Function to delete an existing expedition
void deleteExpedition(vector<Expedition>& expeditions) {
    cout << "Enter the ID of the expedition to delete: ";
    int id;
    cin >> id;

    Expedition* expedition = nullptr;
    for (Expedition& exp : expeditions) {
        if (exp.id == id) {
            expedition = &exp;
            break;
        }
    }

    if (expedition == nullptr) {
        cout << "Expedition not found!" << endl;
        return;
    }

    expeditions.erase(remove(expeditions.begin(), expeditions.end(), *expedition), expeditions.end());

    cout << "Expedition deleted successfully!" << endl;
}

// Function to view crew members of a specific expedition
void viewCrewMembers(vector<Expedition> expeditions) {
    cout << "Enter the ID of the expedition to view crew members: ";
    int id;
    cin >> id;

    Expedition* expedition = nullptr;
    for (Expedition& exp : expeditions) {
        if (exp.id == id) {
            expedition = &exp;
            break;
        }
    }

    if (expedition == nullptr) {
        cout << "Expedition not found!" << endl;
        return;
    }

    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Crew Members of Expedition " << expedition->name << endl;
    cout << "======================================================================================" << endl;
    cout << "Name" << endl;
    for (CrewMember crewMember : expedition->crewMembers) {
        cout << crewMember.name << endl;
    }
    cout << "======================================================================================" << endl;
}

// Function to view crew members with their roles of a specific expedition
void viewCrewMembersWithRoles(vector<Expedition> expeditions) {
    cout << "Enter the ID of the expedition to view crew members with roles: ";
    int id;
    cin >> id;

    Expedition* expedition = nullptr;
    for (Expedition& exp : expeditions) {
        if (exp.id == id) {
            expedition = &exp;
            break;
        }
    }

    if (expedition == nullptr) {
        cout << "Expedition not found!" << endl;
        return;
    }

    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Crew Members with Roles of Expedition " << expedition->name << endl;
    cout << "======================================================================================" << endl;
    cout << "Name\tRole" << endl;
    for (CrewMember crewMember : expedition->crewMembers) {
        cout << crewMember.name << "\t" << crewMember.role << endl;
    }
    cout << "======================================================================================" << endl;
}

// Function to search expeditions by destination
void searchExpeditions(vector<Expedition> expeditions) {
    cout << "Enter the destination to search for: ";
    string destination;
    cin.ignore();
    getline(cin, destination);

    vector<Expedition> matchingExpeditions;
    for (Expedition expedition : expeditions) {
        if (expedition.destination == destination) {
            matchingExpeditions.push_back(expedition);
        }
    }

    if (matchingExpeditions.empty()) {
        cout << "No expeditions found for the destination: " << destination << endl;
        return;
    }

    viewExpeditions(matchingExpeditions);
}

// Function to save expedition data to a file
void saveData(const vector<Expedition>& expeditions, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Expedition& expedition : expeditions) {
            file << expedition.id << "," << expedition.name << "," << expedition.destination << "," << expedition.status << ",";
            for (const CrewMember& crewMember : expedition.crewMembers) {
                file << crewMember.name << ":" << crewMember.role << ";";
            }
            file << endl;
        }
        file.close();
        cout << "Data saved successfully!" << endl;
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

// Function to add a crew member to an existing expedition
void addCrewMember(vector<Expedition>& expeditions) {
    cout << "Enter the ID of the expedition to add a crew member: ";
    int id;
    cin >> id;

    Expedition* expedition = nullptr;
    for (Expedition& exp : expeditions) {
        if (exp.id == id) {
            expedition = &exp;
            break;
        }
    }

    if (expedition == nullptr) {
        cout << "Expedition not found!" << endl;
        return;
    }

    cout << "Enter crew member name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    cout << "Select crew member role:" << endl;
    for (int j = 0; j < crewRoles.size(); ++j) {
        cout << j + 1 << ". " << crewRoles[j].name << endl;
    }
    cout << "Enter your choice: ";
    int roleChoice;
    cin >> roleChoice;
    if (roleChoice < 1 || roleChoice > crewRoles.size()) {
        cout << "Invalid role choice!" << endl;
        return;
    }
    string role = crewRoles[roleChoice - 1].name;

    CrewMember crewMember;
    crewMember.name = name;
    crewMember.role = role;

    expedition->crewMembers.push_back(crewMember);

    cout << "Crew member added successfully!" << endl;
}

// Function to remove a crew member from an existing expedition
void removeCrewMember(vector<Expedition>& expeditions) {
    cout << "Enter the ID of the expedition to remove a crew member: ";
    int id;
    cin >> id;

    Expedition* expedition = nullptr;
    for (Expedition& exp : expeditions) {
        if (exp.id == id) {
            expedition = &exp;
            break;
        }
    }

    if (expedition == nullptr) {
        cout << "Expedition not found!" << endl;
        return;
    }

    cout << "Enter the name of the crew member to remove: ";
    string name;
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (auto it = expedition->crewMembers.begin(); it != expedition->crewMembers.end(); ++it) {
        if (it->name == name) {
            expedition->crewMembers.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Crew member removed successfully!" << endl;
    }
    else {
        cout << "Crew member not found!" << endl;
    }
}

// Function to load expedition data from a file
void loadData(vector<Expedition>& expeditions, const string& filename) {
    expeditions.clear();

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Expedition expedition;
            size_t pos = 0;
            string token;
            while ((pos = line.find(",")) != string::npos) {
                token = line.substr(0, pos);
                expedition.id = stoi(token);
                line.erase(0, pos + 1);

                pos = line.find(",");
                token = line.substr(0, pos);
                expedition.name = token;
                line.erase(0, pos + 1);

                pos = line.find(",");
                token = line.substr(0, pos);
                expedition.destination = token;
                line.erase(0, pos + 1);

                pos = line.find(",");
                token = line.substr(0, pos);
                expedition.status = static_cast<ExpeditionStatus>(stoi(token));
                line.erase(0, pos + 1);

                pos = line.find(";");
                while ((pos = line.find(";")) != string::npos) {
                    CrewMember crewMember;
                    token = line.substr(0, pos);
                    size_t colonPos = token.find(":");
                    crewMember.name = token.substr(0, colonPos);
                    crewMember.role = token.substr(colonPos + 1);
                    expedition.crewMembers.push_back(crewMember);
                    line.erase(0, pos + 1);
                }
            }
            expeditions.push_back(expedition);
        }
        file.close();
        cout << "Data loaded successfully!" << endl;
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

// Function to calculate distance to a destination planet
void calculateDistance() {
    cout << "Enter the ID of the destination planet: ";
    int id;
    cin >> id;

    if (id < 1 || id > solarSystem.size()) {
        cout << "Invalid planet ID!" << endl;
        return;
    }

    int planetIndex = id - 1;

    double distance = solarSystem[planetIndex].distanceFromEarth;
    cout << "Distance to the destination planet " << solarSystem[planetIndex].name << ": " << distance << " million kilometers" << endl;
}
int main() {
    vector<Expedition> expeditions;

    int choice;
    do {
        choice = displayMainMenu();

        switch (choice) {
        case NEW_EXPEDITION:
            createExpedition(expeditions);
            break;
        case VIEW_EXPEDITIONS:
            viewExpeditions(expeditions);
            break;
        case EDIT_EXPEDITION:
            editExpedition(expeditions);
            break;
        case DELETE_EXPEDITION:
            deleteExpedition(expeditions);
            break;
        case VIEW_CREW_MEMBERS:
            viewCrewMembers(expeditions);
            break;
        case ADD_CREW_MEMBER:
            addCrewMember(expeditions);
            break;
        case REMOVE_CREW_MEMBER:
            removeCrewMember(expeditions);
            break;
        case VIEW_CREW_MEMBERS_WITH_ROLES:
            viewCrewMembersWithRoles(expeditions);
            break;
        case SEARCH_EXPEDITIONS:
            searchExpeditions(expeditions);
            break;
        case SAVE_DATA:
            saveData(expeditions, "expeditions.csv");
            break;
        case LOAD_DATA:
            loadData(expeditions, "expeditions.csv");
            break;
        case CALCULATE_DISTANCE:
            calculateDistance();
            break;
        case EXIT:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 13." << endl;
            break;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != EXIT);

    return 0;
}
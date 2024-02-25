#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

// Структура за планета в слънчевата система
struct Planet {
    string name;
    double distanceFromEarth; // Разстояние от Земята в милиони километри
};

// Структура за роля на член на екипажа
struct Role {
    string name;
};

// Структура за космически кораб
struct SpaceshipOption {
    string name;
    double speed; // Например, скорост в км/ч
    double capacity; // Например, капацитет на горивния резервоар в литри
};

// Списък с планети в слънчевата система
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

// Списък с роли на членовете на екипажа
vector<Role> crewRoles = {
    {"Captain"},
    {"Navigator"},
    {"Engineer"},
    {"Pilot"},
    {"Medic"},
    {"Scientist"},
    {"Crew Member"} // Новата роля
};

// Списък с опции за космически кораби
vector<SpaceshipOption> spaceshipOptions = {
    {"Falcon", 100000, 10000},
    {"Starblazer", 120000, 12000},
    {"Nebula Voyager", 90000, 8000},
    {"Galaxy Runner", 110000, 11000},
    {"Cosmo Strider", 95000, 9000},
    {"Stellar Cruiser", 115000, 10000}
};

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

enum ExpeditionStatus {
    PLANNED,
    IN_PROGRESS,
    COMPLETED,
    CANCELED
};

struct CrewMember {
    string name;
    string role;
};

struct Expedition {
    int id;
    string name;
    string destination;
    ExpeditionStatus status;
    vector<CrewMember> crewMembers;
    double distance;

    bool operator==(const Expedition& other) const {
        return id == other.id;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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

    // Променете индекса на планетата тук, за да съответства на индексацията от 0 до N-1
    int planetIndex = planetChoice - 1;

    // Извеждане на избраната дестинация
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

    // Проверка за максимален брой членове на екипажа
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

    // Изчисляване на разстоянието до дестинацията
    double distance = 0.0;
    for (int i = 0; i < planetIndex; ++i) {
        distance += solarSystem[i].distanceFromEarth;
    }
    expedition.distance = distance;

    expeditions.push_back(expedition);

    cout << "Expedition created successfully!" << endl;
}

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

void calculateDistance() {
    cout << "Enter the ID of the destination planet: ";
    int id;
    cin >> id;

    if (id < 1 || id > solarSystem.size()) {
        cout << "Invalid planet ID!" << endl;
        return;
    }

    double distance = solarSystem[id - 1].distanceFromEarth;
    cout << "Distance to the destination planet " << solarSystem[id - 1].name << ": " << distance << " million kilometers" << endl;
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
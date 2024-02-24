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

// Enum за ролите на членовете на екипажа
enum CrewRole {
    PILOT = 1,
    ENGINEER,
    SCIENTIST,
    NAVIGATOR,
    COMMUNICATIONS_OFFICER,
    MEDIC,
    CREW_MEMBER // Новата роля
};

enum ExpeditionStatus {
    PLANNED,
    IN_PROGRESS,
    COMPLETED,
    CANCELED
};

struct CrewMember {
    string name;
    CrewRole role; // Променен тип на ролята
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

int displayCrewRoles() {
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Select Crew Role" << endl;
    cout << "======================================================================================" << endl;
    cout << "1. Pilot" << endl;
    cout << "2. Engineer" << endl;
    cout << "3. Scientist" << endl;
    cout << "4. Navigator" << endl;
    cout << "5. Communications Officer" << endl;
    cout << "6. Medic" << endl;
    cout << "7. Crew Member" << endl;
    cout << "Enter role number: ";

    int choice;
    cin >> choice;
    return choice;
}

void createExpedition(vector<Expedition>& expeditions) {
    cout << "Enter expedition name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    int planetChoice = displaySpaceshipOptions();
    if (planetChoice < 1 || planetChoice > spaceshipOptions.size()) {
        cout << "Invalid spaceship choice!" << endl;
        return;
    }

    string destination = spaceshipOptions[planetChoice - 1].name;

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

        int roleChoice = displayCrewRoles();
        if (roleChoice < 1 || roleChoice > CREW_MEMBER) {
            cout << "Invalid role choice!" << endl;
            return;
        }

        crewMember.role = static_cast<CrewRole>(roleChoice);

        crewMembers.push_back(crewMember);
    }

    Expedition expedition;
    expedition.id = expeditions.size() + 1;
    expedition.name = name;
    expedition.destination = destination;
    expedition.status = expeditionStatus;
    expedition.crewMembers = crewMembers;

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
        cout << crewMember.name << "\t";
        switch (crewMember.role) {
        case PILOT:
            cout << "Pilot";
            break;
        case ENGINEER:
            cout << "Engineer";
            break;
        case SCIENTIST:
            cout << "Scientist";
            break;
        case NAVIGATOR:
            cout << "Navigator";
            break;
        case COMMUNICATIONS_OFFICER:
            cout << "Communications Officer";
            break;
        case MEDIC:
            cout << "Medic";
            break;
        case CREW_MEMBER:
            cout << "Crew Member";
            break;
        default:
            cout << "Unknown Role";
            break;
        }
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}

void searchExpeditions(const vector<Expedition>& expeditions) {
    cout << "Enter the name or destination to search: ";
    string query;
    cin.ignore();
    getline(cin, query);

    bool found = false;
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Search Results" << endl;
    cout << "======================================================================================" << endl;
    cout << "ID\tName\tDestination\tStatus" << endl;
    for (const Expedition& exp : expeditions) {
        if (exp.name.find(query) != string::npos || exp.destination.find(query) != string::npos) {
            found = true;
            cout << exp.id << "\t" << exp.name << "\t" << exp.destination << "\t";

            string status;
            switch (exp.status) {
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
    }

    if (!found) {
        cout << "No matching expeditions found." << endl;
    }
    cout << "======================================================================================" << endl;
}

void saveData(const vector<Expedition>& expeditions, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const Expedition& exp : expeditions) {
            outputFile << exp.id << "," << exp.name << "," << exp.destination << "," << exp.status << ",";
            for (const CrewMember& crewMember : exp.crewMembers) {
                outputFile << crewMember.name << ":" << crewMember.role << ";";
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Data saved successfully." << endl;
    }
    else {
        cout << "Unable to open file for saving." << endl;
    }
}

void loadData(vector<Expedition>& expeditions, const string& filename) {
    expeditions.clear();
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            Expedition exp;
            size_t pos = line.find(",");
            exp.id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            exp.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            exp.destination = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            exp.status = static_cast<ExpeditionStatus>(stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);

            while (!line.empty()) {
                pos = line.find(":");
                string name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(";");
                CrewRole role = static_cast<CrewRole>(stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);

                exp.crewMembers.push_back({ name, role });
            }

            expeditions.push_back(exp);
        }
        inputFile.close();
        cout << "Data loaded successfully." << endl;
    }
    else {
        cout << "Unable to open file for loading. Creating new file." << endl;
    }
}

double calculateDistanceToEarth(const string& destination) {
    for (const Planet& planet : solarSystem) {
        if (planet.name == destination) {
            return planet.distanceFromEarth;
        }
    }
    return -1.0; // Връщаме -1, ако не е намерена дестинацията
}

void calculateDistanceToEarthMenu() {
    clearScreen();
    cout << "======================================================================================" << endl;
    cout << "Calculate Distance to Earth" << endl;
    cout << "======================================================================================" << endl;
    cout << "Enter the destination: ";
    string destination;
    cin >> destination;
    double distance = calculateDistanceToEarth(destination);
    if (distance >= 0) {
        cout << "Distance to Earth from " << destination << " is " << distance << " million kilometers." << endl;
    }
    else {
        cout << "Destination not found in the solar system." << endl;
    }
}

int main() {
    vector<Expedition> expeditions;

    while (true) {
        int choice = displayMainMenu();

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
            cout << "This option is not yet implemented." << endl;
            break;
        case REMOVE_CREW_MEMBER:
            cout << "This option is not yet implemented." << endl;
            break;
        case VIEW_CREW_MEMBERS_WITH_ROLES:
            viewCrewMembersWithRoles(expeditions);
            break;
        case SEARCH_EXPEDITIONS:
            searchExpeditions(expeditions);
            break;
        case SAVE_DATA:
            saveData(expeditions, "expeditions.txt");
            break;
        case LOAD_DATA:
            loadData(expeditions, "expeditions.txt");
            break;
        case CALCULATE_DISTANCE:
            calculateDistanceToEarthMenu();
            break;
        case EXIT:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }

    return 0;
}

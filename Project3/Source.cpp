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

struct Planet {
    string name;
    double distanceFromEarth;
};

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

enum CrewRole {
    CAPTAIN,
    PILOT,
    ENGINEER,
    SCIENTIST,
    MEDIC,
    COMMUNICATIONS_OFFICER
};

struct CrewMember {
    string name;
    CrewRole role;
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

int displaySolarSystemMenu() {
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

    int planetChoice = displaySolarSystemMenu();
    if (planetChoice < 1 || planetChoice > solarSystem.size()) {
        cout << "Invalid planet choice!" << endl;
        return;
    }

    string destination = solarSystem[planetChoice - 1].name;

    cout << "Enter expedition status (1 for Planned, 2 for In Progress, 3 for Completed, 4 for Canceled): ";
    int status;
    cin >> status;

    ExpeditionStatus expeditionStatus = static_cast<ExpeditionStatus>(status);

    vector<CrewMember> crewMembers;

    cout << "Enter the number of crew members: ";
    int numCrewMembers;
    cin >> numCrewMembers;

    if (numCrewMembers > 15) {
        cout << "Maximum number of crew members allowed is 15!" << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < numCrewMembers; i++) {
        CrewMember crewMember;
        cout << "Enter crew member name: ";
        getline(cin, crewMember.name);

        cout << "Select crew member role (1 for Captain, 2 for Pilot, 3 for Engineer, 4 for Scientist, 5 for Medic, 6 for Communications Officer): ";
        int roleChoice;
        cin >> roleChoice;

        if (roleChoice < 1 || roleChoice > 6) {
            cout << "Invalid role choice!" << endl;
            return;
        }

        crewMember.role = static_cast<CrewRole>(roleChoice - 1);
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

string getCrewRoleName(CrewRole role) {
    switch (role) {
    case CAPTAIN:
        return "Captain";
    case PILOT:
        return "Pilot";
    case ENGINEER:
        return "Engineer";
    case SCIENTIST:
        return "Scientist";
    case MEDIC:
        return "Medic";
    case COMMUNICATIONS_OFFICER:
        return "Communications Officer";
    default:
        return "Member";
    }
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
    cout << "Name\tRole" << endl;
    for (CrewMember crewMember : expedition->crewMembers) {
        cout << crewMember.name << "\t" << getCrewRoleName(crewMember.role) << endl;
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
        cout << crewMember.name << "\t" << getCrewRoleName(crewMember.role) << endl;
    }
    cout << "======================================================================================" << endl;
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
            saveData(expeditions);
            break;
        case LOAD_DATA:
            loadData(expeditions);
            break;
        case CALCULATE_DISTANCE:
            calculateExpeditionDistance(expeditions);
            break;
        case EXIT:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

        if (choice != EXIT) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != EXIT);

    return 0;
}

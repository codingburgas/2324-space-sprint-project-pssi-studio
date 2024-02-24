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

void createExpedition(vector<Expedition>& expeditions) {
    cout << "Enter expedition name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    cout << "Enter expedition destination: ";
    string destination;
    getline(cin, destination);

    cout << "Enter expedition status (1 for Planned, 2 for In Progress, 3 for Completed, 4 for Canceled): ";
    int status;
    cin >> status;

    ExpeditionStatus expeditionStatus = static_cast<ExpeditionStatus>(status);

    vector<CrewMember> crewMembers;

    cout << "Enter the number of crew members: ";
    int numCrewMembers;
    cin >> numCrewMembers;

    cin.ignore();
    for (int i = 0; i < numCrewMembers; i++) {
        CrewMember crewMember;
        cout << "Enter crew member name: ";
        getline(cin, crewMember.name);
        cout << "Enter crew member role: ";
        getline(cin, crewMember.role);
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
        cout << crewMember.name << "\t" << crewMember.role << endl;
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
    for (const Expedition& expedition : expeditions) {
        if (expedition.name.find(query) != string::npos || expedition.destination.find(query) != string::npos) {
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
            found = true;
        }
    }
    if (!found) {
        cout << "No matching expeditions found." << endl;
    }
    cout << "======================================================================================" << endl;
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

    cout << "Enter the name of the crew member to add: ";
    cin.ignore();
    string name;
    getline(cin, name);

    cout << "Enter the role of the crew member: ";
    string role;
    getline(cin, role);

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
    cin.ignore();
    string crewMemberName;
    getline(cin, crewMemberName);

    auto it = find_if(expedition->crewMembers.begin(), expedition->crewMembers.end(),
        [&crewMemberName](const CrewMember& member) {
            return member.name == crewMemberName;
        });

    if (it == expedition->crewMembers.end()) {
        cout << "Crew member not found in the expedition!" << endl;
        return;
    }

    expedition->crewMembers.erase(it);

    cout << "Crew member removed successfully!" << endl;
}

void saveData(const vector<Expedition>& expeditions) {
    ofstream outputFile("expeditions.txt");
    if (outputFile.is_open()) {
        for (const Expedition& expedition : expeditions) {
            outputFile << expedition.id << "," << expedition.name << "," << expedition.destination << "," << expedition.status << ",";
            for (const CrewMember& crewMember : expedition.crewMembers) {
                outputFile << crewMember.name << ":" << crewMember.role << ";";
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Data saved successfully!" << endl;
    }
    else {
        cout << "Unable to open file for saving data!" << endl;
    }
}

void loadData(vector<Expedition>& expeditions) {
    expeditions.clear();
    ifstream inputFile("expeditions.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            Expedition expedition;
            size_t pos = 0;
            string token;
            while ((pos = line.find(",")) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                expedition.id = stoi(token);

                pos = line.find(",");
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                expedition.name = token;

                pos = line.find(",");
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                expedition.destination = token;

                pos = line.find(",");
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                expedition.status = static_cast<ExpeditionStatus>(stoi(token));

                pos = line.find(";");
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                size_t colonPos = token.find(":");
                CrewMember crewMember;
                crewMember.name = token.substr(0, colonPos);
                crewMember.role = token.substr(colonPos + 1);
                expedition.crewMembers.push_back(crewMember);
            }
            expeditions.push_back(expedition);
        }
        inputFile.close();
        cout << "Data loaded successfully!" << endl;
    }
    else {
        cout << "Unable to open file for loading data!" << endl;
    }
}

double calculateDistance(const Expedition& expedition) {
    // Placeholder function for distance calculation, replace with actual logic
    return 1000.0; // Placeholder value
}

void calculateExpeditionDistance(vector<Expedition>& expeditions) {
    cout << "Enter the ID of the expedition to calculate distance: ";
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

    double distance = calculateDistance(*expedition);
    expedition->distance = distance;
    cout << "Distance calculated for Expedition " << expedition->name << ": " << distance << " units" << endl;
}

int main() {
    vector<Expedition> expeditions;

    loadData(expeditions);

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
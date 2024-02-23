#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

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

    bool operator==(const Expedition& other) const {
        return id == other.id;
    }
};

int displayMainMenu() {
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
    cout << "12. Exit" << endl;
    cout << "======================================================================================" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    system("CLS");
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
    system("PAUSE");
    system("CLS");
}

void viewExpeditions(vector<Expedition> expeditions) {
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
    system("PAUSE");
    system("CLS");
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
    system("PAUSE");
    system("CLS");
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
    system("PAUSE");
    system("CLS");
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

    cout << "======================================================================================" << endl;
    cout << "Crew Members of Expedition " << expedition->name << endl;
    cout << "======================================================================================" << endl;
    cout << "Name" << endl;
    for (CrewMember crewMember : expedition->crewMembers) {
        cout << crewMember.name << endl;
    }

    cout << "======================================================================================" << endl;
    system("PAUSE");
    system("CLS");
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

    cout << "======================================================================================" << endl;
    cout << "Crew Members with Roles of Expedition " << expedition->name << endl;
    cout << "======================================================================================" << endl;
    cout << "Name\tRole" << endl;
    for (CrewMember crewMember : expedition->crewMembers) {
        cout << crewMember.name << "\t" << crewMember.role << endl;
    }

    cout << "======================================================================================" << endl;
    system("PAUSE");
    system("CLS");
}

void searchExpeditions(const vector<Expedition>& expeditions) {
    cout << "Enter the name or destination to search: ";
    string query;
    cin.ignore();
    getline(cin, query);

    bool found = false;
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
    system("PAUSE");
    system("CLS");
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
    system("PAUSE");
    system("CLS");
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
    system("PAUSE");
    system("CLS");
}

void saveExpeditionsToFile(const vector<Expedition>& expeditions) {
    ofstream outputFile("expeditions.txt");

    if (!outputFile) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (const Expedition& expedition : expeditions) {
        outputFile << expedition.id << "," << expedition.name << "," << expedition.destination << "," << expedition.status << endl;
        for (const CrewMember& crewMember : expedition.crewMembers) {
            outputFile << crewMember.name << "," << crewMember.role << endl;
        }
        outputFile << endl;
    }

    outputFile.close();

    cout << "Expeditions saved to file successfully!" << endl;
    system("PAUSE");
    system("CLS");
}

void loadExpeditionsFromFile(vector<Expedition>& expeditions) {
    ifstream inputFile("expeditions.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    expeditions.clear();

    while (inputFile) {
        Expedition expedition;
        string line;
        if (!getline(inputFile, line)) {
            break;
        }

        istringstream ss(line);
        string token;
        getline(ss, token, ',');
        expedition.id = stoi(token);
        getline(ss, token, ',');
        expedition.name = token;
        getline(ss, token, ',');
        expedition.destination = token;
        getline(ss, token, ',');
        expedition.status = static_cast<ExpeditionStatus>(stoi(token));

        while (getline(inputFile, line)) {
            if (line.empty()) {
                break;
            }
            CrewMember crewMember;
            istringstream ss(line);
            getline(ss, crewMember.name, ',');
            getline(ss, crewMember.role, ',');
            expedition.crewMembers.push_back(crewMember);
        }

        expeditions.push_back(expedition);
    }

    inputFile.close();

    cout << "Expeditions loaded from file successfully!" << endl;
    system("PAUSE");
    system("CLS");
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
            saveExpeditionsToFile(expeditions);
            break;
        case LOAD_DATA:
            loadExpeditionsFromFile(expeditions);
            break;
        case EXIT:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != EXIT);

    return 0;
}

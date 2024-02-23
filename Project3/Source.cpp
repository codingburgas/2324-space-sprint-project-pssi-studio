#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

enum MainMenuOptions {
    NEW_EXPEDITION = 1,
    VIEW_EXPEDITIONS,
    EDIT_EXPEDITION,
    DELETE_EXPEDITION,
    VIEW_CREW_MEMBERS,
    ADD_CREW_MEMBER,
    REMOVE_CREW_MEMBER,
    EXIT
};

enum ExpeditionStatus {
    PLANNED,
    IN_PROGRESS,
    COMPLETED,
    CANCELED
};

struct Expedition {
    int id;
    string name;
    string destination;
    ExpeditionStatus status;
    vector<string> crewMembers;
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
    cout << "8. Exit" << endl;
    cout << "======================================================================================" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

void createExpedition(vector<Expedition>& expeditions) {
    cout << "Enter expedition name: ";
    string name;
    cin >> name;

    cout << "Enter expedition destination: ";
    string destination;
    cin >> destination;

    cout << "Enter expedition status (1 for Planned, 2 for In Progress, 3 for Completed, 4 for Canceled): ";
    int status;
    cin >> status;

    ExpeditionStatus expeditionStatus = static_cast<ExpeditionStatus>(status);

    vector<string> crewMembers;

    cout << "Enter the number of crew members: ";
    int numCrewMembers;
    cin >> numCrewMembers;

    for (int i = 0; i < numCrewMembers; i++) {
        cout << "Enter crew member name: ";
        string crewMember;
        cin >> crewMember;
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
    string name;
    cin >> name;

    cout << "Enter new expedition destination: ";
    string destination;
    cin >> destination;

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

    cout << "======================================================================================" << endl;
    cout << "Crew Members of Expedition " << expedition->name << endl;
    cout << "======================================================================================" << endl;

    cout << "Name" << endl;

    for (string crewMember : expedition->crewMembers) {
        cout << crewMember << endl;
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
    string crewMember;
    cin >> crewMember;

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
    string crewMember;
    cin >> crewMember;

    auto it = find(expedition->crewMembers.begin(), expedition->crewMembers.end(), crewMember);

    if (it == expedition->crewMembers.end()) {
        cout << "Crew member not found in the expedition!" << endl;
        return;
    }

    expedition->crewMembers.erase(it);

    cout << "Crew member removed successfully!" << endl;
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
        case EXIT:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }

    } while (choice != EXIT);

    return 0;
}

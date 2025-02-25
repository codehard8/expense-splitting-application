#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include "Dashboard.h"
#include "Login.h"
#include "Expense.h"

using namespace std;

void writeExpenseToFile(const string& fileName, const string& payer, const string& description, double amount) {
    ofstream outFile(fileName, ios::app);
    if (outFile) {
        outFile << payer << "," << description << "," << amount << endl;
    } else {
        cerr << "Error: Could not open file " << fileName << endl;
    }
}

void displayExpensesFromFile(const string& fileName) { 
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }

    cout << "+-----+----------------------+------------------------------+------------+" << endl;
    cout << "| S.No | Name                 | Description                  | Amount     |" << endl;
    cout << "+-----+----------------------+------------------------------+------------+" << endl;

    string line;
    int serialNo = 1;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        string payer = line.substr(0, pos1);
        string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        double amount = stod(line.substr(pos2 + 1));

        cout << "| " << setw(4) << serialNo++ << " | "
             << setw(18) << left << payer << " | "
             << setw(28) << left << description << " | "
             << setw(10) << right << fixed << setprecision(2) << amount << " |" << endl;
    }

    cout << "+-----+----------------------+------------------------------+------------+" << endl;
    inFile.close();
}

int main() {
    if (!std::filesystem::exists("Data")) {
        std::filesystem::create_directory("Data");
    }

    Dashboard dashboard;
    Login login;

    string username, password, email, description, payer, friendName, user;
    double amount;
    int choice, expenseChoice, numMembers;
    vector<string> members;
    

   cout <<  "███████╗██████╗ ██╗     ██╗████████╗██╗    ██╗██╗███████╗███████╗\n";
    cout << "██╔════╝██╔══██╗██║     ██║╚══██╔══╝██║    ██║██║██╔════╝██╔════╝\n";
    cout << "███████╗██████╔╝██║     ██║   ██║   ██║ █╗ ██║██║███████╗█████╗  \n";
    cout << "╚════██║██╔═══╝ ██║     ██║   ██║   ██║███╗██║██║╚════██║██╔══╝  \n";
    cout << "███████║██║     ███████╗██║   ██║   ╚███╔███╔╝██║███████║███████╗\n";
    cout << "╚══════╝╚═╝     ╚══════╝╚═╝   ╚═╝    ╚══╝╚══╝ ╚═╝╚══════╝╚══════╝\n";
    cout << "                                                                  \n";

    cout << "Welcome to SplitWise App!" << endl;

    // User registration/login
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter email: ";
    cin >> email;
    while (!login.isValidEmail(email)) {
        cout << "Invalid email format. Please try again: ";
        cin >> email;
    }
    cout << "Enter password: ";
    cin >> password;

    login.setUsername(username);
    login.setEmail(email);
    login.setPassword(password);

    cout << "Login successful!" << endl;

    do {
        cout << "\nMain Menu" << endl;
        cout << "1. Add Personal Expense" << endl;
        cout << "2. Add Friend Expense" << endl;
        cout << "3. Add Group Expense" << endl;
        cout << "4. Settle Up Amount" << endl;
        cout << "5. View All Expenses" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        switch (choice) {
            case 1:
                cout << "Personal Expense" << endl;
                cin.ignore();
                cout << "Enter expense description: ";
                getline(cin, description);

                cout << "Enter amount: ";
                while (!(cin >> amount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                payer = username;
                dashboard.addPersonalExpense(description, amount, payer);
                break;

            case 2:
                cout << "Friend Expense" << endl;
                cout << "Enter friend's name: ";
                cin >> friendName;
                cin.ignore();
                cout << "Enter expense description: ";
                getline(cin, description);

                cout << "Enter amount: ";
                while (!(cin >> amount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                payer = username;
                dashboard.addFriendExpense(description, amount, payer, friendName);
                break;

            case 3:
                cout << "Group Expense" << endl;
                cin.ignore();
                cout << "Enter description: ";
                getline(cin, description);

                cout << "Enter amount: ";
                while (!(cin >> amount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                cout << "Enter number of group members: ";
                while (!(cin >> numMembers)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid number of members: ";
                }

                cout << "Enter Payer name: ";
                cin >> payer;
                members.clear();
                cin.ignore();
                cout << "Enter group members' names:" << endl;
                for (int i = 0; i < numMembers; ++i) {
                    string member;
                    getline(cin, member);
                    members.push_back(member);
                }

                dashboard.addGroupExpense(description, amount, payer, members);
                break;

            case 4:
                cout << "Enter username to settle up: ";
                cin >> user;
                dashboard.settleUpAmount(user);
                break;

            case 5:
                cout << "1 : Personal Expense" << endl;
                cout << "2 : Group Expense" << endl;
                cout << "3 : Friend Expense" << endl;

                cout << "Enter your choice: ";
                while (!(cin >> expenseChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid choice: ";
                }

                switch (expenseChoice) {
                    case 1:
                        displayExpensesFromFile("Data/PersonalExpense.txt");
                        break;
                    case 2:
                        displayExpensesFromFile("Data/GroupExpense.txt");
                        break;
                    case 3:
                        displayExpensesFromFile("Data/FriendExpense.txt");
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                break;

            case 6:
                cout << "Exiting the app..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

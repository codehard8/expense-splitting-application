#include "Expense.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Expense constructor
Expense::Expense(string description=0, double Amount=0, string Payer=0) {
    this->description = description;
    this->amount = Amount;
    this->payer = Payer;
}

// Static function to display expenses from a file
void Expense::displayFromFile(const string& fileName) {
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
        // Skip empty lines
        if (line.empty()) continue;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            cerr << "Error: Invalid format in file" << endl;
            continue;
        }

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

// Common display function for all expenses
void Expense::displayExpenseDetails() const {
    cout << "| S.No | Name                 | Description                  | Amount     |" << endl;
    cout << "|  1   | " << setw(18) << left << payer 
         << " | " << setw(28) << left << description 
         << " | " << setw(10) << right << fixed << setprecision(2) << amount << " |" << endl;
}

// PersonalExpense constructor
PersonalExpense::PersonalExpense(string description, double Amount, string Payer)
    : Expense(description, Amount, Payer){}

// Display Expense Details for PersonalExpense
void PersonalExpense::displayExpense() const {
    displayExpenseDetails();
}

// Write to file for PersonalExpense
void PersonalExpense::writeToFile(ofstream& outFile) const {
    outFile << payer << "," << description << "," << amount << endl;
}

// FriendExpense constructor
FriendExpense::FriendExpense(string description, double Amount, string Payer, string friendName)
    : Expense(description, Amount, Payer), friendName(friendName) {}

// Display Expense Details for FriendExpense
void FriendExpense::displayExpense() const {
    displayExpenseDetails();
    cout << "Friend: " << friendName << endl;  // Optionally, print the friend's name.
}

// Write to file for FriendExpense
void FriendExpense::writeToFile(ofstream& outFile) const {
    outFile << payer << "," << description << "," << amount << "," << friendName << endl;
}

// GroupExpense constructor
GroupExpense::GroupExpense(string description, double Amount, string Payer, vector<string> groupMembers)
    : Expense(description, Amount, Payer), groupMembers(groupMembers) {}

// Display Expense Details for GroupExpense
void GroupExpense::displayExpense() const {
    displayExpenseDetails();
    cout << "Group Members: ";
    for (const auto& member : groupMembers) {
        cout << member << " ";
    }
    cout << endl;
}

// Write to file for GroupExpense
void GroupExpense::writeToFile(ofstream& outFile) const {
    outFile << payer << "," << description << "," << amount << ",";
    for (const auto& member : groupMembers) {
        outFile << member << " ";
    }
    outFile << endl;
}

#include "Dashboard.h"
#include "Expense.h"
#include <iostream>
#include <fstream>

void Dashboard::addPersonalExpense(const string& description, double amount, const string& payer) {
    PersonalExpense expense(description, amount, payer);
    ofstream personalFile("Data/PersonalExpense.txt", ios::app);
    if (personalFile) {
        expense.writeToFile(personalFile);
    } else {
        cerr << "Error: Could not open file for personal expense." << endl;
    }
}

void Dashboard::addFriendExpense(const string& description, double amount, const string& payer, const string& friendName) {
    FriendExpense expense(description, amount, payer, friendName);
    ofstream friendFile("Data/FriendExpense.txt", ios::app);
    if (friendFile) {
        friendFile << friendName << "," << description << "," << amount << endl;
    } else {
        cerr << "Error: Could not open file for friend expense." << endl;
    }
}

void Dashboard::addGroupExpense(const string& description, double amount, const string& payer, const vector<string>& groupMembers) {
    GroupExpense expense(description, amount, payer, groupMembers);
    ofstream groupFile("Data/GroupExpense.txt", ios::app);
    if (groupFile) {
        groupFile << payer << "," << description << "," << amount << endl;
    } else {
        cerr << "Error: Could not open file for group expense." << endl;
    }
}

void Dashboard::settleUpAmount(const string& payer) {
    // Implement logic to settle up amounts between users (e.g., calculate the share each person owes).
    cout << "Settling up amounts for " << payer << "...\n";
}

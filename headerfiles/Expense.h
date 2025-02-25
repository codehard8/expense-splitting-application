#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

using namespace std;

// Base class for all types of expenses
class Expense {
protected:
    string description;
    double amount;
    string payer;

public:
    // Constructor
    Expense(string description, double Amount, string Payer);

    // Static function to display expenses from a file
    static void displayFromFile(const string& fileName);

    // Common display function for all expenses
    void displayExpenseDetails() const;

    // Virtual display function for each expense type
    virtual void displayExpense() const = 0;

    // Write to file (pure virtual function)
    virtual void writeToFile(ofstream& outFile) const = 0;
};

// Derived class for personal expenses
class PersonalExpense : public Expense {
public:
    // Constructor
    PersonalExpense(string description, double Amount, string Payer);

    // Override display function
    void displayExpense() const override;

    // Write to file
    void writeToFile(ofstream& outFile) const override;
};

// Derived class for friend-related expenses
class FriendExpense : public Expense {
private:
    string friendName;

public:
    // Constructor
    FriendExpense(string description, double Amount, string Payer, string friendName);

    // Override display function
    void displayExpense() const override;

    // Write to file
    void writeToFile(ofstream& outFile) const override;
};

// Derived class for group-related expenses
class GroupExpense : public Expense {
private:
    vector<string> groupMembers;

public:
    // Constructor
    GroupExpense(string description, double Amount, string Payer, vector<string> groupMembers);

    // Override display function
    void displayExpense() const override;

    // Write to file
    void writeToFile(ofstream& outFile) const override;
};

#endif // EXPENSE_H

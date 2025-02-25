#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include "Expense.h"

class Dashboard {
public:
    void addPersonalExpense(const string& description, double amount, const string& payer);
    void addFriendExpense(const string& description, double amount, const string& payer, const string& friendName);
    void addGroupExpense(const string& description, double amount, const string& payer, const vector<string>& groupMembers);
    void settleUpAmount(const string& payer);
};

#endif // DASHBOARD_H

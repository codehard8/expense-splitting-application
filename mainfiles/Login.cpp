#include "Login.h"
#include <iostream>
#include <regex>

Login::Login() : username(""), email(""), password("") {}

void Login::setUsername(const string& username) {
    this->username = username;
}

void Login::setEmail(const string& email) {
    this->email = email;
}

void Login::setPassword(const string& password) {
    this->password = password;
}

// Simple email validation using regex
bool Login::isValidEmail(const string& email) {
    const regex pattern("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    return regex_match(email, pattern);
}

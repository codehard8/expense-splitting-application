#ifndef LOGIN_H
#define LOGIN_H

#include <string>
using namespace std;

class Login {
public:
	//parameters
    string username;
    string email;
    string password;
    
    //  constructor
    Login();
    // methods
    void setUsername(const string& username);
    void setEmail(const string& email);
    void setPassword(const string& password);

    bool isValidEmail(const string& email);
};

#endif // LOGIN_H

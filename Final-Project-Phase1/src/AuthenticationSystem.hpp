#ifndef AUTHENTICATION_SYSTEM_H
#define AUTHENTICATION_SYSTEM_H
#include <iostream>
#include <string>
#include <vector>
#include "Session.hpp"
#include "User.hpp"
class AuthenticationSystem
{
public:
	AuthenticationSystem();
	void login(std::vector<User*> users,std::string email,std::string password);
	void logout();
private:
	Session *current_session;
	void create_new_session(User *user);
};
#endif
#ifndef AUTHENTICATION_SYSTEM_H
#define AUTHENTICATION_SYSTEM_H
#include <iostream>
#include <string>
#include <vector>
#include "Session.hpp"
#include "User.hpp"
#include "XOREncryption.hpp"
class AuthenticationSystem
{
public:
	AuthenticationSystem();
	~AuthenticationSystem();
	void login(std::vector<User*> users,std::string email,std::string password);
	bool check_login(std::vector<User*> users,std::string email,std::string password);
	void logout();
	bool is_logged_in();
	Session* get_session(){return current_session;}
private:
	Session *current_session;
	void create_new_session(User *user);
};
#endif
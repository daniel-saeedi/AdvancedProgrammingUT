#include "User.hpp"
bool User::is_email_username_equal(std::string _email,std::string _username)
{
	if(email == _email || username == _username) return true;
	return false;
}

bool User::check_email_password(std::string _email,std::string _password)
{
	if(email == _email && password == _password) return true;
	return false;
}

bool User::is_username_equal(std::string _username)
{
	if(username == _username) return true;
	return false;
}

void User::print_username()
{
	std::cout << username << std::endl;
}
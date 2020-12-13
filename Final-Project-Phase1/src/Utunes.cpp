#include "Utunes.hpp"
#include "Exception/BadRequestException.hpp"
Utunes::Utunes(vector<Song*> _songs) : songs(_songs)
{
	auth_sys = new AuthenticationSystem();
}

void Utunes::signup(vector<std::string> signup_info)
{
	std::string email;
	std::string username;
	std::string password;
	for(int i = 0;i < signup_info.size();i++)
	{
		if(signup_info[i] == "email") email = signup_info[i+1];
		else if(signup_info[i] == "username") username = signup_info[i+1];
		else if(signup_info[i] == "password") password = signup_info[i+1];
	}
	create_new_user(email,username,password);
	std::cout << "OK" << std::endl;
}

void Utunes::create_new_user(std::string email,std::string username,std::string password)
{
	if(email_username_exists(email,username)) throw BadRequestException();
	User *new_user = new User(email,username,password);
	users.push_back(new_user);
}

bool Utunes::email_username_exists(std::string email,std::string username)
{
	for(int i = 0;i < users.size();i++)
	{
		if(users[i]->is_email_username_equal(email,username)) return true;
	}
	return false;
}










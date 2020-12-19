#include "AuthenticationSystem.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/PermissionDeniedException.hpp"

AuthenticationSystem::AuthenticationSystem()
{
	current_session = nullptr;
}

AuthenticationSystem::~AuthenticationSystem()
{
	if(current_session != nullptr) delete current_session;
}

void AuthenticationSystem::login(std::vector<User*> users,std::string email,std::string password)
{
	User *user = nullptr;
	for(int i = 0;i < users.size();i++)
	{
		if(users[i]->check_email_password(email,password)) user = users[i];
	}
	if(user == nullptr) throw BadRequestException();
	create_new_session(user);
}

void AuthenticationSystem::create_new_session(User *user)
{
	current_session = new Session(user);
}

void AuthenticationSystem::logout()
{
	if(current_session == nullptr) throw PermissionDeniedException();
	delete current_session;
	current_session = nullptr;
}

bool AuthenticationSystem::is_logged_in()
{
	if(current_session == nullptr) throw PermissionDeniedException();
}
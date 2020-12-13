#ifndef UTUNES_H
#define UTUNES_H
#include "AuthenticationSystem.hpp"
#include "Song.hpp"
#include "User.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Utunes
{
public:
	Utunes(vector <Song*> _songs);
	void signup(vector<std::string> signup_info);
private:
	AuthenticationSystem *auth_sys;
	vector<Song*> songs;
	vector<User*> users;
	bool email_username_exists(std::string email,std::string username);
	void create_new_user(std::string email,std::string username,std::string password);
};
#endif
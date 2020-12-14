#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "Playlist.hpp"
class Song;
class User
{
public:
	User(std::string _email,std::string _username,std::string _password) 
	: email(_email),username(_username),password(_password){}
	bool is_email_username_equal(std::string _email,std::string _username);
	bool check_email_password(std::string _email,std::string _password);
	//void add_playlist(int id,std::string name,bool private_status) ;
private:
	std::string email;
	std::string username;
	std::string password;
	//vector<Playlist*> playlists;
};
#endif
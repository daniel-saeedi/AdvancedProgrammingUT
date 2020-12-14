#ifndef UTUNES_H
#define UTUNES_H
#include "AuthenticationSystem.hpp"
#include "Song.hpp"
#include "User.hpp"
#include "Session.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Utunes
{
public:
	Utunes(vector <Song*> _songs);
	void signup(vector<std::string> signup_info);
	void login(vector<std::string> login_info);
	void logout();
	void check_login();
	void get_songs();
	void get_song(vector<std::string> song_id);
	void new_like(vector<std::string> song_id);
	void delete_like(vector<std::string> song_id);
	void show_likes();
private:
	AuthenticationSystem *auth_sys;
	vector<Song*> songs;
	vector<User*> users;
	bool email_username_exists(std::string email,std::string username);
	void create_new_user(std::string email,std::string username,std::string password);
	void print_ok();
	void show_songs();
	bool song_exists(int id);
	Song* find_song_by_id(int id);
	vector<Song*> get_liked_songs();
	int extract_id(vector<std::string> song_id);
};
#endif
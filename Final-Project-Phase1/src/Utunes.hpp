#ifndef UTUNES_H
#define UTUNES_H
#include "AuthenticationSystem.hpp"
#include "Song.hpp"
#include "User.hpp"
#include "Session.hpp"
#include "PlaylistSystem.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
class Utunes
{
public:
	Utunes(vector <Song*> _songs);
	~Utunes();
	void signup(vector<std::string> signup_info);
	void login(vector<std::string> login_info);
	void logout();
	void check_login();
	void get_songs();
	void get_song(vector<std::string> song_id);
	void new_like(vector<std::string> song_id);
	void delete_like(vector<std::string> song_id);
	void show_likes();
	void add_playlist(vector<std::string> playlist_info);
	void get_playlists(vector<std::string> playlist_info);
	void add_song_to_playlist(vector<std::string> playlist_info);
	void get_playlist_songs(vector<std::string> playlist_info);
	void delete_playlist_song(vector<std::string> playlist_info);
	void get_users();
	void add_comment(vector<std::string> playlist_info);
	void get_comments(vector<std::string> playlist_info);
	void add_filter(vector<std::string> filter_info);
	void delete_filters();
private:
	AuthenticationSystem *auth_sys;
	PlaylistSystem *playlist_sys;
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
	User* find_user(std::string username);
	bool user_exists(std::string username);
	void add_artist_filter(vector<std::string> filter_info);
	void add_publish_year_filter(vector<std::string> filter_info);
	void add_likes_filter(vector<std::string> filter_info);
	std::map<std::string,std::string> split(vector<std::string> headers,vector<std::string> info);
};
#endif
#ifndef UTUNES_H
#define UTUNES_H
#include "AuthenticationSystem.hpp"
#include "Song.hpp"
#include "User.hpp"
#include "Session.hpp"
#include "PlaylistSystem.hpp"
#include "RecommendationSystem.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
class Utunes
{
public:
	Utunes(vector <Song*> _songs);
	~Utunes();
	void signup(std::string email,std::string username,std::string password,bool printok = true);
	void login(std::string email,std::string password);
	void logout(bool printok = true);
	void check_login();
	void get_songs();
	void get_song(int id);
	void new_like(int id,bool printok = true);
	void delete_like(int song_id);
	void show_likes();
	void add_playlist(std::string name,bool private_status);
	void get_playlists(std::string username);
	void add_song_to_playlist(int playlist_id,int song_id);
	void get_playlist_songs(int playlist_id);
	void delete_playlist_song(int playlist_id,int song_id);
	void get_users();
	void add_comment(int song_id,int time,std::string comment);
	void get_comments(int song_id);
	void delete_filters();
	void add_artist_filter(std::string artist);
	void add_publish_year_filter(int min_year,int max_year);
	void add_likes_filter(int min_like,int max_like);
	bool user_exists(std::string username);
	void get_similar_users(int count);
	void get_recommendation(int count);
	std::vector<Song*> get_songs_vector(){return songs;}
	int get_users_count(){return users.size();}
	Song* find_song_by_id(int id);
	RecommendationSystem* get_recommendation_sys(){return recommendation_sys;}
	PlaylistSystem* get_playlist_sys(){return playlist_sys;}
	std::vector<Song*> get_recommended_songs();
	User* get_current_user(){return auth_sys->get_session()->get_user();}
	vector<Song*> get_liked_songs();
private:
	AuthenticationSystem *auth_sys;
	PlaylistSystem *playlist_sys;
	RecommendationSystem *recommendation_sys;
	vector<Song*> songs;
	vector<User*> users;
	bool email_username_exists(std::string email,std::string username);
	void create_new_user(std::string email,std::string username,std::string password);
	void print_ok();
	void show_songs();
	bool song_exists(int id);
	User* find_user(std::string username);
};
#endif
#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include <vector>
#include "Song.hpp"
#include "User.hpp"

class Playlist
{
public:
	Playlist(int _id,std::string _name,bool _private_status,User *_user) 
		: id(_id), name(_name), private_status(_private_status), user(_user){}
	bool is_user_equal(User *_user);
	void show_info(User *current_user);
	void add_song(Song *song,User *current_user);
	void show_songs(User *current_user);
	void delete_song(Song *song,User *current_user);
	int get_id(){return id;}
	bool song_exists(Song *song);
	bool is_playlist_id_equal(int _id);
	bool is_private(){return private_status;}
private:
	int id;
	std::string name;
	bool private_status;
	User *user;
	std::vector<Song*> songs;
	void print_info();
	void check_permission(User *current_user);
};
#endif
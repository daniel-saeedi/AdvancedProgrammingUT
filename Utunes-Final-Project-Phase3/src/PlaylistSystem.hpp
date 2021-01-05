#ifndef PLAYLIST_SYSTEM_H
#define PLAYLIST_SYSTEM_H
#include "Song.hpp"
#include "User.hpp"
#include "Playlist.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class PlaylistSystem
{
public:
	~PlaylistSystem();
	void new_playlist(std::string name,bool private_status,User *user);
	void show_playlist(User *user,User *current_user);
	void add_song_to_playlist(int playlist_id,Song *song,User *current_user);
	void show_playlist_songs(int playlist_id,User *current_user);
	void delete_song(int playlist_id,Song *song,User *current_user);
	int count_playlists_contain_song(Song *song);
	vector<Playlist*> find_playlist(User *user);
	vector<Playlist*> get_playlists(User *user);
	Playlist* get_playlist_by_index(int playlist_id,User *current_user);
private:
	vector<Playlist*> playlists;
	int get_playlist_index(int playlist_id);
};
#endif
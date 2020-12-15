#include "PlaylistSystem.hpp"
#include "Exception/EmptyException.hpp"

void PlaylistSystem::new_playlist(std::string name,bool private_status,User *user)
{
	int id = playlists.size();
	Playlist* playlist = new Playlist(id,name,private_status,user);
	playlists.push_back(playlist);
	std::cout << id << std::endl;
}

void PlaylistSystem::show_playlist(User *user,User *current_user)
{
	vector<Playlist*> lists = find_playlist(user);
	if(lists.size() == 0) throw EmptyException();
	for(int i = 0;i < lists.size();i++)
	{
		lists[i]->show_info(current_user);
	}
}

void PlaylistSystem::add_song_to_playlist(int playlist_id,Song *song,User *current_user)
{
	//Correct This!!!!!!!!!!
	if(playlist_id >= playlists.size()) throw EmptyException();
	playlists[playlist_id]->add_song(song,current_user);
}

void PlaylistSystem::show_playlist_songs(int playlist_id,User *current_user)
{
	//Correct This!!!!!!!!!!
	if(playlist_id >= playlists.size()) throw EmptyException();
	
	playlists[playlist_id]->show_songs(current_user);
}

void PlaylistSystem::delete_song(int playlist_id,Song *song,User *current_user)
{
	//Correct This!!!!!!!!!!
	if(playlist_id >= playlists.size()) throw EmptyException();
	playlists[playlist_id]->delete_song(song,current_user);
}

vector<Playlist*> PlaylistSystem::find_playlist(User *user)
{
	vector<Playlist*> lists;
	for(int i = 0;i < playlists.size();i++)
	{
		if(playlists[i]->is_user_equal(user)) lists.push_back(playlists[i]);
	}
	return lists;
}
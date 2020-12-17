#include "PlaylistSystem.hpp"
#include "Exception/EmptyException.hpp"

bool compare_by_id_playlists(Playlist *playlist1,Playlist *playlist2)
{
	return playlist1->get_id() < playlist2->get_id();
}

void PlaylistSystem::new_playlist(std::string name,bool private_status,User *user)
{
	int id = playlists.size() + 1;
	Playlist* playlist = new Playlist(id,name,private_status,user);
	playlists.push_back(playlist);
	std::cout << id << std::endl;
}

void PlaylistSystem::show_playlist(User *user,User *current_user)
{
	vector<Playlist*> lists = find_playlist(user);
	sort(lists.begin(),lists.end(),compare_by_id_playlists);
	if(lists.size() == 0) throw EmptyException();
	for(int i = 0;i < lists.size();i++)
	{
		lists[i]->show_info(current_user);
	}
}

void PlaylistSystem::add_song_to_playlist(int playlist_id,Song *song,User *current_user)
{
	int index = get_playlist_index(playlist_id);
	playlists[index]->add_song(song,current_user);
}

void PlaylistSystem::show_playlist_songs(int playlist_id,User *current_user)
{
	int index = get_playlist_index(playlist_id);
	playlists[index]->show_songs(current_user);
}

void PlaylistSystem::delete_song(int playlist_id,Song *song,User *current_user)
{
	int index = get_playlist_index(playlist_id);
	playlists[index]->delete_song(song,current_user);
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

int PlaylistSystem::count_playlists_contain_song(Song *song)
{
	int count = 0;
	for(int i = 0;i < playlists.size();i++)
	{
		if(playlists[i]->song_exists(song)) count++;
	}
	return count;
}

int PlaylistSystem::get_playlist_index(int playlist_id)
{
	int index = -1;
	for(int i = 0;i < playlists.size();i++)
	{
		if(playlists[i]->is_playlist_id_equal(playlist_id)) index = i;
	}
	if(index == -1) throw EmptyException();
	return index;
}
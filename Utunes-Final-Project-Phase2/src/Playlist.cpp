#include <algorithm>
#include "Playlist.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/PermissionDeniedException.hpp"
#include "Exception/EmptyException.hpp"
constexpr char PRIVATE[] = "private";
constexpr char PUBLIC[] = "public";

bool compare_song_by_id(Song *song1,Song *song2)
{
	return song1->get_id() < song2->get_id();
}

bool Playlist::is_user_equal(User *_user)
{
	if(user == _user) return true;
	else return false;
}

bool Playlist::is_playlist_id_equal(int _id)
{
	if(id == _id) return true;
	else return false;
}

void Playlist::show_info(User *current_user)
{
	if(private_status == false) print_info();
	else if(private_status == true && current_user == user) print_info();
}

void Playlist::print_info()
{
	std::cout << id << " ";
	std::cout << name << " ";
	if(private_status) std::cout << PRIVATE << std::endl;
	else std::cout << PUBLIC << std::endl;
}

void Playlist::add_song(Song *song,User *current_user)
{
	if(user != current_user) throw PermissionDeniedException();
	if(!song_exists(song)) songs.push_back(song);
}

void Playlist::delete_song(Song *song,User *current_user)
{
	if(user != current_user) throw PermissionDeniedException();
	if(!song_exists(song)) throw BadRequestException();
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i] == song)
			songs.erase(songs.begin() + i);
	}
}

void Playlist::show_songs(User *current_user)
{
	if(user != current_user && private_status) throw PermissionDeniedException();
	if(songs.size() == 0) throw EmptyException();
	sort(songs.begin(),songs.end(),compare_song_by_id);
	for(int i = 0;i < songs.size();i++)
	{
		songs[i]->print_info();
	}
}

void Playlist::check_permission(User *current_user)
{
	if(user != current_user && private_status) throw PermissionDeniedException();
}

bool Playlist::song_exists(Song *song)
{
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i] == song) return true;
	}
	return false;
}
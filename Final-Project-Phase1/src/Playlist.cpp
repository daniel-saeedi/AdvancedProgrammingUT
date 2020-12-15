#include "Playlist.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/PermissionDeniedException.hpp"
#include "Exception/EmptyException.hpp"
constexpr char PRIVATE[] = "private";
constexpr char PUBLIC[] = "public";

bool Playlist::is_user_equal(User *_user)
{
	if(user == _user) return true;
	else false;
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
	if(private_status) std::cout << PRIVATE << " ";
	else std::cout << PUBLIC << std::endl;
}

void Playlist::add_song(Song *song,User *current_user)
{
	check_permission(current_user);
	if(!song_exists(song)) songs.push_back(song);
}

void Playlist::delete_song(Song *song,User *current_user)
{
	check_permission(current_user);
	if(!song_exists(song)) throw BadRequestException();
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i] == song)
			songs.erase(songs.begin() + i);
	}
}

void Playlist::show_songs(User *current_user)
{
	//write CheckPermission function
	check_permission(current_user);
	if(songs.size() == 0) throw EmptyException();
	for(int i = 0;i < songs.size();i++)
	{
		songs[i]->print_info();
	}
}

void Playlist::check_permission(User *current_user)
{
	if(user != current_user) throw PermissionDeniedException();
}

bool Playlist::song_exists(Song *song)
{
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i] == song) return true;
	}
	return false;
}










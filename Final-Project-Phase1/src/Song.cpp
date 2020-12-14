#include "Song.hpp"

void Song::print_info()
{
	std::cout << id << " ";
	std::cout << title << " ";
	std::cout << artist << " ";
	std::cout << release_year << std::endl;
}

void Song::print_single_info()
{
	std::cout << id << std::endl;
	std::cout << title << std::endl;
	std::cout << artist << std::endl;
	std::cout << release_year << std::endl;
}

bool Song::is_equal(int _id)
{
	if(id == _id) return true;
	return false;
}

void Song::like(User *user)
{
	like_sys->like(user);
}

bool Song::has_liked(User *user)
{
	return like_sys->like_exists(user);
}

void Song::delete_like(User *user)
{
	like_sys->delete_like(user);
}
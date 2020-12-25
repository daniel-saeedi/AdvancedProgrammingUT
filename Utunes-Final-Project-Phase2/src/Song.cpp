#include "Song.hpp"
constexpr char LIKES_MARK[] = "#likes: ";
constexpr char COMMENTS_MARK[] = "#comments: ";
void Song::print_info()
{
	std::cout << id << " ";
	std::cout << title << " ";
	std::cout << artist << " ";
	std::cout << release_year << std::endl;
}

void Song::print_info(double confidence)
{
	std::cout << id << " ";
	std::cout << confidence << "% ";
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
	std::cout << LIKES_MARK << get_likes() << std::endl;
	std::cout << COMMENTS_MARK << get_total_comments() << std::endl;
}

bool Song::is_equal(int _id)
{
	if(id == _id) return true;
	return false;
}

bool Song::is_artist_equal(std::string _artist)
{
	if(artist == _artist) return true;
	return false;
}